
/*
    Voronoi Map Generator core.
    Each library used contains its license.
    See "voronoi_data.h" for other code licences.
*/

#ifndef VORONOI_H
#define VORONOI_H

#include "voronoi_data.h"

namespace voronoi {

    class VoronoiMap
    {
    private:
        // Random generator
        ygl::rng_pcg32 rng;

        // Const params
        const float WATER_PERC = 0.3f;
        const float LAVA_PERC = 0.2f;
        const int LAVA_WATER_DIST = 12;
        const float LAVA_MAX_MOISTURE = 0.15f;
        const float LAVA_MIN_ELEVATION = 0.9f;
        const float MIN_RIVER_ELEVATION = 0.3f;
        const float MAX_RIVER_ELEVATION = 0.7f;

        // Voronoi data
        float map_side;
        float n_points;
        float n_relaxations;
        float max_xy;
        ygl::map<int, vcell*> cells;
        ygl::map<ygl::string, vertex*> vertices;
        ygl::vector<ygl::vector<vertex*>> vbuckets;

        // Map options
        const map_options* options;

        // Utils
        ygl::vec3f to_world(const ygl::vec2f& p, float y);
        ygl::vec2f to_world_norm(const ygl::vec2f& p);
        bool is_border(const ygl::vec2f& p);

        // Diagram Generation
        vertex* make_vertex(const jcv_point& p);
        vcell* make_cell(const jcv_site* site);
        void generate_diagram();

        // Map Generation
        void generate_islands();
        void generate_rivers();
        void generate_moisture();
        void generate_lava();
        void generate_colors();

    public:
        VoronoiMap(float map_side, int n_points, int n_relaxation, const map_options* opt);
        ~VoronoiMap();

        ygl::scene* generate_scene();
    };

    /*
    -----------------------------------------------------------------------------
    Voronoi Private - Utils
    -----------------------------------------------------------------------------
    */

    inline ygl::vec3f VoronoiMap::to_world(const ygl::vec2f& p, float y = 0.0f)
    {
        return { (float)p.x - (this->map_side / 2.0f), y, (float)p.y - (this->map_side / 2.0f) };
    }

    inline ygl::vec2f VoronoiMap::to_world_norm(const ygl::vec2f& p)
    {
        return { 2.0f * ((p.x / this->map_side) - 0.5f), 2.0f * ((p.y / this->map_side) - 0.5f) };
    }

    inline bool VoronoiMap::is_border(const ygl::vec2f& p)
    {
        return p.x <= BORDER_EPS || p.y <= BORDER_EPS || p.x >= this->map_side - BORDER_EPS || p.y >= this->map_side - BORDER_EPS;
    }

    /*
    -----------------------------------------------------------------------------
    Voronoi Private - Diagram Generation
    -----------------------------------------------------------------------------
    */

    vertex* VoronoiMap::make_vertex(const jcv_point& p)
    {
        // Search for a vertex close the point
        for (auto v : this->vbuckets[(int)p.x])
            if (ygl::length(v->p - get_vec2f(p)) < POINT_EPS)
                return v;

        // If not found, create it
        auto v = new vertex(p);
        this->vertices[v->id] = v;
        this->vbuckets[(int)p.x].push_back(v);
        v->border = this->is_border(v->p);
        return v;
    }

    vcell* VoronoiMap::make_cell(const jcv_site* site)
    {
        // Create a new cell only if exists anymore
        auto res = this->cells.find(site->index);
        if (res == this->cells.end())
        {
            auto cell = new vcell(site);
            this->cells[cell->id] = cell;
            return cell;
        }
        else
            return res->second;
    }

    void VoronoiMap::generate_diagram()
    {
        printf("VoronoiMap:Diagram -> Building diagram\n");
        auto diagram = build_jc_voronoi(this->map_side, this->n_points, this->n_relaxations);

        printf("VoronoiMap:Diagram -> Wrapping diagram\n");
        auto sites = jcv_diagram_get_sites(diagram);
        for (int i = 0; i < diagram->numsites; ++i)
        {
            // Get site and create the relative cell
            auto site = &sites[i];
            auto d0 = this->make_cell(site);

            // Get half edges list of the cell
            auto ge = site->edges;

            // Save the first vertex, because is the also the last
            auto first_v = ge->pos[0];

            // Foreach half edge
            while (ge)
            {
                /*
                    We need to convert half edges in full edges, 
                    so each edge created go from the first vertex of half edge 'n' 
                    to the first vertex of half edge 'n + 1'.
                    In this mesh the edges are NOT shared.
                */
                
                // Make vertices
                auto v0 = this->make_vertex(ge->pos[0]);
                vertex* v1;
                if (ge->next)
                    v1 = this->make_vertex(ge->next->pos[0]);
                else
                    v1 = this->make_vertex(first_v);

                // Associate the two vertices to each other
                add_once(v0->adjacent, v1);
                add_once(v1->adjacent, v0);

                edge* e;
                if (ge->neighbor)
                {
                    // Edge with neighbor -> the edge connect d0 and d1
                    auto d1 = this->make_cell(ge->neighbor);
                    e = new edge(v0, v1, d0, d1);

                    // Mark d0 and d1 as neighbours
                    add_once(d1->neighbors, d0);
                    add_once(d0->neighbors, d1);
                }
                else
                {
                    // Edge without neighbor -> d0 is border
                    d0->border = true;
                    e = new edge(v0, v1);
                }

                // Associate vertices to d0
                add_once(v0->touches, d0);
                add_once(v1->touches, d0);
                add_once(d0->vertices, v0);
                add_once(d0->vertices, v1);

                // Add the edge to d0
                d0->edges.push_back(e);

                ge = ge->next;
            }
        }

        // Free old diagram
        jcv_diagram_free(diagram);
    }

    /*
    -----------------------------------------------------------------------------
    Voronoi Private - Map Generation
    -----------------------------------------------------------------------------
    */

    void VoronoiMap::generate_islands()
    {
        // Adapted from: https://github.com/redblobgames/mapgen2/

        // Work queues
        std::deque<vertex*> border1;
        std::deque<vertex*> border2;
        std::deque<vertex*> shore;

        // Mark water vertices (and remember border vertices)
        for (auto vertex_pair : this->vertices)
        {
            auto v = vertex_pair.second;
            v->water = v->border || is_island(this->to_world_norm(v->p), this->options);

            if (v->border)
            {
                border1.push_back(v);
                border2.push_back(v);
            }
        }
        
        // Mark shore and beach vertices
        while (!border1.empty())
        {
            auto v = border1.front();
            border1.pop_front();
            v->coast_dist = 0;
            for (auto adj_pair : v->adjacent)
            {
                auto adj = adj_pair.second;
                if(!adj->water)
                {
                    v->shore = true;
                    v->coast_dist = 0;
                    adj->beach = true;
                    shore.push_back(v);
                }
                else if(adj->coast_dist < 0)
                    border1.push_back(adj);
            }
        }
        
        // Mark ocean vertices
        while (!border2.empty())
        {
            auto v = border2.front();
            border2.pop_front();

            if (!v->water || v->shore || v->beach)
                continue;

            v->ocean = true;
            for (auto adj_pair : v->adjacent)
            {
                auto adj = adj_pair.second;
                if (adj->water && !adj->shore && !adj->beach && !adj->ocean)
                    border2.push_back(adj);
            }
        }

        // Set vertices downslope and coast_dist (using BFS and shore queue)
        auto max_dist = 1;
        while (!shore.empty())
        {
            auto v = shore.front();
            shore.pop_front();

            for (auto adj_pair : v->adjacent)
            {
                auto adj = adj_pair.second;

                if (adj->water && adj->ocean)
                    continue;

                // If adj is lake or beach, not increase the distance
                adj->lake = adj->water && !adj->ocean;
                auto same_dist = adj->lake || adj->beach;

                auto new_dist = (same_dist ? 0 : 1) + v->coast_dist;
                if (!adj->shore && (adj->coast_dist < 0 || new_dist < adj->coast_dist))
                {
                    adj->downslope = v;
                    adj->coast_dist = new_dist;
                    if (new_dist > max_dist)
                        max_dist = new_dist;
                    if (same_dist)
                        shore.push_front(adj);
                    else
                        shore.push_back(adj);
                }
            }
        }

        // Set vertices elevation
        for (auto vertex_pair : this->vertices)
        {
            auto v = vertex_pair.second;
            v->elevation = (float)v->coast_dist / (float)max_dist;
        }
    }

    void VoronoiMap::generate_rivers()
    {
        // Adapted from: https://github.com/redblobgames/mapgen2/
        
        // If can't create rivers, exit
        if (this->options->n_rivers <= 0)
            return;

        // Search vertices that can be a river start point (if not found, exit)
        ygl::vector<vertex*> rivers;
        for (auto v_pair : this->vertices)
        {
            auto v = v_pair.second;
            if (v->water || v->beach || v->shore)
                continue;
            if (v->elevation >= MIN_RIVER_ELEVATION && v->elevation <= MAX_RIVER_ELEVATION)
                rivers.push_back(v);
        }
        if (rivers.empty())
            return;

        // Fix wrong rivers number
        if (this->options->n_rivers > rivers.size())
            throw ygl::runtime_error("Generate rivers: " + std::to_string(this->options->n_rivers) + " rivers cannot be generated");

        // Shuffle the river start vertex list
        ygl::rng_shuffle(this->rng, rivers);

        // Make rivers
        auto i = 0;
        while (i < this->options->n_rivers)
        {
            // Pick a random vertex from the list (if it is already a river, pick another vertex)
            auto v = rivers.at(ygl::next_rand1i(this->rng, rivers.size() - 1));
            if (v->river)
                continue;

            do
            {
                // This vertex is the join point of two rivers
                if (v->river)
                    break;

                // Set the vertex as a river
                v->river = true;
                v->water = true;
                v->ocean = false;
                v->shore = false;
                v->beach = false;

                // Go to the next vertices towards the ocean
                v = v->downslope;
            } while (v);

            i++;
        }
    }

    void VoronoiMap::generate_moisture()
    {
        // Adapted from: https://github.com/redblobgames/mapgen2/
        
        // Collect rivers and lakes vertices
        std::deque<vertex*> vmoisture;
        for (auto v_pair : this->vertices)
        {
            auto v = v_pair.second;
            if (v->water)
                vmoisture.push_back(v);
        }

        // Assign moisture
        auto max_dist = 1;
        while (!vmoisture.empty())
        {
            auto v = vmoisture.front();
            vmoisture.pop_front();

            for (auto adj_pair : v->adjacent)
            {
                auto adj = adj_pair.second;
                auto new_dist = v->water_dist + 1;
                if (!adj->water && (adj->water_dist == 0 || new_dist < adj->water_dist))
                {
                    adj->water_dist = new_dist;
                    if (new_dist > max_dist)
                        max_dist = new_dist;
                    vmoisture.push_back(adj);
                }
            }
        }

        // Assing vertices moisture
        for (auto v_pair : this->vertices)
        {
            auto v = v_pair.second;
            v->moisture = v->water ? 1.0f : 1.0f - powf((float)v->water_dist / (float)max_dist, 0.5f);
        }
    }

    void VoronoiMap::generate_lava()
    {
        // Adapted from: https://github.com/redblobgames/mapgen2/

        // Search vertices that can be a lava point (must be an high and dry point)
        ygl::vector<vertex*> vlava;
        for (auto v_pair : this->vertices)
        {
            auto v = v_pair.second;
            if (!v->water && v->water_dist >= LAVA_WATER_DIST && 
                v->elevation >= LAVA_MIN_ELEVATION && v->moisture <= LAVA_MAX_MOISTURE)
                vlava.push_back(v);
        }
        if (vlava.empty())
            return;
        
        // Shuffle the lava vertex list
        ygl::rng_shuffle(this->rng, vlava);

        // Mark some vertices as lava
        for (auto i = 0; i < ceil(vlava.size() * LAVA_PERC); i++)
            vlava[i]->lava = true;
    }

    void VoronoiMap::generate_colors()
    {
        // Adapted from: https://github.com/redblobgames/mapgen2/
        
        // The color of a vertex is based on its properties
        for (auto v_pair : this->vertices)
        {
            auto v = v_pair.second;
            v->color = get_color(get_biome(v));
        }

        // The cells color is the average of it's vertices color
        // Compute also the cells elevation, that is still the average 
        for (auto cell_pair : this->cells)
        {
            auto cell = cell_pair.second;
            auto is_river_end = false;
            auto sum_elevations = 0.0f;
            auto sum_colors = ygl::zero4f;
            auto n_vertices = (float)cell->vertices.size();
            for (auto vertex_pair : cell->vertices)
            {
                auto v = vertex_pair.second;

                // If the cell touches a river end, cell center is river
                if (v->river && !v->downslope)
                    is_river_end = true;
                
                sum_colors += v->color;
                sum_elevations += v->elevation;
            }
            cell->elevation = sum_elevations / n_vertices;
            cell->color = is_river_end ? get_color("river") : sum_colors / n_vertices;
        }
    }

    /*
    -----------------------------------------------------------------------------
    Voronoi Public Methods
    -----------------------------------------------------------------------------
    */

    VoronoiMap::VoronoiMap(float map_side, int n_points, int n_relaxations, const map_options* opt)
    {
        printf("VoronoiMap -> Init\n");

        if (map_side <= 4.0f || n_points < 1000 || n_relaxations < 2 || !check_options(opt))
            throw ygl::runtime_error("VoronoiMap: bad init params");

        // Init params
        this->map_side = map_side;
        this->n_points = n_points;
        this->n_relaxations = n_relaxations;
        this->max_xy = map_side + 2.0f;
        this->options = opt;

        // Init random generator and vertices buckets
        this->rng = ygl::init_rng(time(0));
        vbuckets = ygl::vector<ygl::vector<vertex*>>(ceil(map_side) + 1, ygl::vector<vertex*>());

        printf("VoronoiMap -> Generating Diagram\n");
        this->generate_diagram();
        
        printf("VoronoiMap -> Generating Islands\n");
        this->generate_islands();

        printf("VoronoiMap -> Generating Rivers\n");
        this->generate_rivers();

        printf("VoronoiMap -> Generating Moisture\n");
        this->generate_moisture();

        printf("VoronoiMap -> Generating Lava\n");
        this->generate_lava();

        printf("VoronoiMap -> Generating Colors\n");
        this->generate_colors();
    }

    VoronoiMap::~VoronoiMap()
    {
        for (auto cell : this->cells)
            if (cell.second) delete cell.second;
        for (auto vertex : this->vertices)
            if (vertex.second) delete vertex.second;
    }

    ygl::scene* VoronoiMap::generate_scene()
    {
        /*
        Generate a scene ready to be saved.
        Automatically center the Voronoi map to the scene center.
        */

        printf("VoronoiMap -> Generating Scene\n");

        auto scn = new ygl::scene();

        // Add cameras
        add_camera(scn, "cam_front", { 0.0f, 30.0f, 50.0f });
        add_camera(scn, "cam_rear", { 0.0f, 30.0f, -50.0f });
        add_camera(scn, "cam_bottom_right", { 40.0f, 25.0f, 25.0f });
        add_camera(scn, "cam_bottom_left", { -40.0f, 25.0f, 25.0f });
        add_camera(scn, "cam_top_right", { 40.0f, 25.0f, -25.0f });
        add_camera(scn, "cam_top_left", { -40.0f, 25.0f, -25.0f });

        // Create scene shape with white material
        auto shp = new ygl::shape();
        shp->name = "scene_shp";
        shp->mat = get_material("white");

        // Fill all cells in the scene
        auto i = 0;
        for (auto cell_pair : this->cells)
        {
            auto cell = cell_pair.second;

            // Add cell center and save its index
            shp->pos += this->to_world(cell->center, cell->elevation * this->options->max_elevation);
            shp->color += cell->color;
            auto i_cell = i++;

            for (auto e : cell->edges)
            {
                // Add edge vertices and save their indexes
                shp->pos += this->to_world(e->v0->p, e->v0->elevation * this->options->max_elevation);
                shp->pos += this->to_world(e->v1->p, e->v1->elevation * this->options->max_elevation);
                shp->color += e->v0->color;
                shp->color += e->v1->color;
                auto i_v0 = i++;
                auto i_v1 = i++;

                // Add the triangle between edge and the cell (ensuring that the points order is correct)
                auto cp = ygl::dot(shp->pos[i_v0] - shp->pos[i_cell], shp->pos[i_v1] - shp->pos[i_cell]);
                shp->triangles += (cp >= 0) ? ygl::vec3i{ i_v0, i_cell, i_v1 } : ygl::vec3i{ i_v1, i_v0, i_cell };
            }
        }

        // Compute normals and add to the scene
        shp->norm = ygl::compute_normals(shp->lines, shp->triangles, shp->quads, shp->pos);
        add_instance(scn, "scene_inst", shp);

        return scn;
    }

}

#endif
