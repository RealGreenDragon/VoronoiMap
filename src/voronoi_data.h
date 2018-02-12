
/*
- Project inspired from these articles:
http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/
https://www.redblobgames.com/maps/mapgen2/
https://www.redblobgames.com/maps/terrain-from-noise/
https://www.redblobgames.com/articles/noise/introduction.html
*/

/*
- LICENSE FOR ALL THE CODE FROM: https://github.com/amitp/mapgen2/

Map generation project 2010
<http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/>

License: MIT Open Source license
<http://www.opensource.org/licenses/mit-license.php>

Copyright 2010 Amit J Patel <amitp@cs.stanford.edu>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
- LICENSE FOR ALL THE CODE FROM: https://github.com/redblobgames/mapgen2/

Copyright 2017 Red Blob Games <redblobgames@gmail.com>
License: Apache v2.0 
<http://www.apache.org/licenses/LICENSE-2.0.html>

Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/

TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION

1. Definitions.

"License" shall mean the terms and conditions for use, reproduction,
and distribution as defined by Sections 1 through 9 of this document.

"Licensor" shall mean the copyright owner or entity authorized by
the copyright owner that is granting the License.

"Legal Entity" shall mean the union of the acting entity and all
other entities that control, are controlled by, or are under common
control with that entity. For the purposes of this definition,
"control" means (i) the power, direct or indirect, to cause the
direction or management of such entity, whether by contract or
otherwise, or (ii) ownership of fifty percent (50%) or more of the
outstanding shares, or (iii) beneficial ownership of such entity.

"You" (or "Your") shall mean an individual or Legal Entity
exercising permissions granted by this License.

"Source" form shall mean the preferred form for making modifications,
including but not limited to software source code, documentation
source, and configuration files.

"Object" form shall mean any form resulting from mechanical
transformation or translation of a Source form, including but
not limited to compiled object code, generated documentation,
and conversions to other media types.

"Work" shall mean the work of authorship, whether in Source or
Object form, made available under the License, as indicated by a
copyright notice that is included in or attached to the work
(an example is provided in the Appendix below).

"Derivative Works" shall mean any work, whether in Source or Object
form, that is based on (or derived from) the Work and for which the
editorial revisions, annotations, elaborations, or other modifications
represent, as a whole, an original work of authorship. For the purposes
of this License, Derivative Works shall not include works that remain
separable from, or merely link (or bind by name) to the interfaces of,
the Work and Derivative Works thereof.

"Contribution" shall mean any work of authorship, including
the original version of the Work and any modifications or additions
to that Work or Derivative Works thereof, that is intentionally
submitted to Licensor for inclusion in the Work by the copyright owner
or by an individual or Legal Entity authorized to submit on behalf of
the copyright owner. For the purposes of this definition, "submitted"
means any form of electronic, verbal, or written communication sent
to the Licensor or its representatives, including but not limited to
communication on electronic mailing lists, source code control systems,
and issue tracking systems that are managed by, or on behalf of, the
Licensor for the purpose of discussing and improving the Work, but
excluding communication that is conspicuously marked or otherwise
designated in writing by the copyright owner as "Not a Contribution."

"Contributor" shall mean Licensor and any individual or Legal Entity
on behalf of whom a Contribution has been received by Licensor and
subsequently incorporated within the Work.

2. Grant of Copyright License. Subject to the terms and conditions of
this License, each Contributor hereby grants to You a perpetual,
worldwide, non-exclusive, no-charge, royalty-free, irrevocable
copyright license to reproduce, prepare Derivative Works of,
publicly display, publicly perform, sublicense, and distribute the
Work and such Derivative Works in Source or Object form.

3. Grant of Patent License. Subject to the terms and conditions of
this License, each Contributor hereby grants to You a perpetual,
worldwide, non-exclusive, no-charge, royalty-free, irrevocable
(except as stated in this section) patent license to make, have made,
use, offer to sell, sell, import, and otherwise transfer the Work,
where such license applies only to those patent claims licensable
by such Contributor that are necessarily infringed by their
Contribution(s) alone or by combination of their Contribution(s)
with the Work to which such Contribution(s) was submitted. If You
institute patent litigation against any entity (including a
cross-claim or counterclaim in a lawsuit) alleging that the Work
or a Contribution incorporated within the Work constitutes direct
or contributory patent infringement, then any patent licenses
granted to You under this License for that Work shall terminate
as of the date such litigation is filed.

4. Redistribution. You may reproduce and distribute copies of the
Work or Derivative Works thereof in any medium, with or without
modifications, and in Source or Object form, provided that You
meet the following conditions:

(a) You must give any other recipients of the Work or
Derivative Works a copy of this License; and

(b) You must cause any modified files to carry prominent notices
stating that You changed the files; and

(c) You must retain, in the Source form of any Derivative Works
that You distribute, all copyright, patent, trademark, and
attribution notices from the Source form of the Work,
excluding those notices that do not pertain to any part of
the Derivative Works; and

(d) If the Work includes a "NOTICE" text file as part of its
distribution, then any Derivative Works that You distribute must
include a readable copy of the attribution notices contained
within such NOTICE file, excluding those notices that do not
pertain to any part of the Derivative Works, in at least one
of the following places: within a NOTICE text file distributed
as part of the Derivative Works; within the Source form or
documentation, if provided along with the Derivative Works; or,
within a display generated by the Derivative Works, if and
wherever such third-party notices normally appear. The contents
of the NOTICE file are for informational purposes only and
do not modify the License. You may add Your own attribution
notices within Derivative Works that You distribute, alongside
or as an addendum to the NOTICE text from the Work, provided
that such additional attribution notices cannot be construed
as modifying the License.

You may add Your own copyright statement to Your modifications and
may provide additional or different license terms and conditions
for use, reproduction, or distribution of Your modifications, or
for any such Derivative Works as a whole, provided Your use,
reproduction, and distribution of the Work otherwise complies with
the conditions stated in this License.

5. Submission of Contributions. Unless You explicitly state otherwise,
any Contribution intentionally submitted for inclusion in the Work
by You to the Licensor shall be under the terms and conditions of
this License, without any additional terms or conditions.
Notwithstanding the above, nothing herein shall supersede or modify
the terms of any separate license agreement you may have executed
with Licensor regarding such Contributions.

6. Trademarks. This License does not grant permission to use the trade
names, trademarks, service marks, or product names of the Licensor,
except as required for reasonable and customary use in describing the
origin of the Work and reproducing the content of the NOTICE file.

7. Disclaimer of Warranty. Unless required by applicable law or
agreed to in writing, Licensor provides the Work (and each
Contributor provides its Contributions) on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
implied, including, without limitation, any warranties or conditions
of TITLE, NON-INFRINGEMENT, MERCHANTABILITY, or FITNESS FOR A
PARTICULAR PURPOSE. You are solely responsible for determining the
appropriateness of using or redistributing the Work and assume any
risks associated with Your exercise of permissions under this License.

8. Limitation of Liability. In no event and under no legal theory,
whether in tort (including negligence), contract, or otherwise,
unless required by applicable law (such as deliberate and grossly
negligent acts) or agreed to in writing, shall any Contributor be
liable to You for damages, including any direct, indirect, special,
incidental, or consequential damages of any character arising as a
result of this License or out of the use or inability to use the
Work (including but not limited to damages for loss of goodwill,
work stoppage, computer failure or malfunction, or any and all
other commercial damages or losses), even if such Contributor
has been advised of the possibility of such damages.

9. Accepting Warranty or Additional Liability. While redistributing
the Work or Derivative Works thereof, You may choose to offer,
and charge a fee for, acceptance of support, warranty, indemnity,
or other liability obligations and/or rights consistent with this
License. However, in accepting such obligations, You may act only
on Your own behalf and on Your sole responsibility, not on behalf
of any other Contributor, and only if You agree to indemnify,
defend, and hold each Contributor harmless for any liability
incurred by, or claims asserted against, such Contributor by reason
of your accepting any such warranty or additional liability.

END OF TERMS AND CONDITIONS

APPENDIX: How to apply the Apache License to your work.

To apply the Apache License to your work, attach the following
boilerplate notice, with the fields enclosed by brackets "{}"
replaced with your own identifying information. (Don't include
the brackets!)  The text should be enclosed in the appropriate
comment syntax for the file format. We also recommend that a
file or class name and description of purpose be included on the
same "printed page" as the copyright notice for easier
identification within third-party archives.

Copyright {yyyy} {name of copyright owner}

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef VORONOI_UTILS_H
#define VORONOI_UTILS_H

#include "yocto_utils.h"

#define JC_VORONOI_IMPLEMENTATION
#include "jc_voronoi.h"

#define POINT_EPS 1e-5f
#define BORDER_EPS 1e-2f
#define INVALID_COLOR ygl::vec4f{ -1.0f, -1.0f, -1.0f, -1.0f }

namespace voronoi {

    /*
    -----------------------------------------------------------------------------
    JC_Voronoi Diagram Generator

    See jc_voronoi.h for license and documentation
    -----------------------------------------------------------------------------
    */

    jcv_diagram* build_jc_voronoi(float map_side, int n_points, int n_relaxations)
    {
        // Adapted from example code in jc_voronoi.h

        // Generate random points
        auto rng = ygl::init_rng(time(0));
        jcv_point* points = (jcv_point*)malloc(sizeof(jcv_point) * (size_t)n_points);
        for (int i = 0; i < n_points; ++i)
        {
            points[i].x = (jcv_real)ygl::next_rand1f(rng, 0.0, map_side);
            points[i].y = (jcv_real)ygl::next_rand1f(rng, 0.0, map_side);
        }

        // Define bbox
        jcv_rect* bbox = new jcv_rect{
            jcv_point{ (jcv_real)0, (jcv_real)0 },
            jcv_point{ (jcv_real)map_side, (jcv_real)map_side }
        };

        // Alloc diagram
        jcv_diagram* diagram = (jcv_diagram*)malloc(sizeof(jcv_diagram));

        // Relax diagram
        for (int i = 0; i < n_relaxations; ++i)
        {
            memset(diagram, 0, sizeof(jcv_diagram));
            jcv_diagram_generate(n_points, (const jcv_point*)points, bbox, diagram);

            const jcv_site* sites = jcv_diagram_get_sites(diagram);
            for (int i = 0; i < diagram->numsites; ++i)
            {
                const jcv_site* site = &sites[i];
                jcv_point sum = { 0.0f, 0.0f };
                int count = 0;

                const jcv_graphedge* edge = site->edges;
                while (edge)
                {
                    sum.x += edge->pos[0].x;
                    sum.y += edge->pos[0].y;
                    ++count;
                    edge = edge->next;
                }

                points[site->index].x = sum.x / count;
                points[site->index].y = sum.y / count;
            }

            jcv_diagram_free(diagram);
        }

        // Build diagram
        memset(diagram, 0, sizeof(jcv_diagram));
        jcv_diagram_generate(n_points, (const jcv_point*)points, bbox, diagram);
        return diagram;
    }

    // Get yocto-gl 'vec2f' from 'jcv_point'
    inline ygl::vec2f get_vec2f(const jcv_point& p) { return { p.x, p.y }; }

    /*
    -----------------------------------------------------------------------------
    Voronoi Diagram Items

    Adapted from https://github.com/amitp/mapgen2/
    -----------------------------------------------------------------------------
    */

    struct map_options;
    struct vertex;
    struct vcell;
    struct edge;

    struct map_options
    {
        // Island shape options
        float round = 0.5f;         // Island regularity        Range [0.0f, 1.0f]  (1.0f   = square island)
        float gain = 0.5f;          // Island compactness       Range [0.0f, 1.0f]  (0.0    = one compact island)
        float inflate = 0.4f;       // Island proportion        Range [0.0f, 1.0f]  (1.0f   = fill the scene)
        float lacunarity = 2.0f;    // Island coast compactness Range [0.0f, 10.0f] (10.0f  = coast with more rocks)
        int octaves = 6;            // Island coast regularity  Range [0, 10]       (10     = coast very jagged)

        // Elements options
        int n_rivers = 1;

        // Elevation options
        float max_elevation = 0.0f;

        map_options(float round, float gain, float inflate, float lacunarity, int octaves, float max_elev, int rivers) :
            round(round), gain(gain), inflate(inflate), lacunarity(lacunarity), octaves(octaves),
            max_elevation(max_elev),
            n_rivers(rivers) {}
    };
    inline bool check_options(const map_options* opt)
    {
        // Return true if options are correct, false otherwise
        return
            opt->round >= 0.0f && opt->round <= 1.0f &&
            opt->inflate >= 0.0f && opt->inflate <= 1.0f &&
            opt->lacunarity >= 0.0f && opt->lacunarity <= 10.0f &&
            opt->gain >= 0.0f && opt->gain <= 1.0f &&
            opt->octaves >= 0 && opt->octaves <= 10 &&
            opt->max_elevation >= 0.0f &&
            opt->n_rivers >= 0;
    }

    struct vertex
    {
        // Vertex ID
        const ygl::string id;

        // Relative 2D data (is lake if is water and isn't ocean)
        bool border = false;    // The vertex is at the map border
        bool beach = false;     // The vertex is land and touches water
        bool shore = false;     // The vertex is water and touches land
        bool water = false;     // The vertex is lake, river, or ocean
        bool lake = false;      // The vertex is lake
        bool ocean = false;     // The vertex is ocean
        bool lava = false;      // The vertex is lava

        // River data
        bool river = false;             // The vertex is river
        vertex* downslope = nullptr;    // Next vertex towards the ocean

        // Y axis data
        float elevation = 20.0f; // Range [0.0f ; 1.0f]
        int coast_dist = -1;    // Vertices before the ocean (following downslope path)

        // Moisture data
        float moisture = 0.0f;  // Range [0.0f ; 1.0f]
        int water_dist = 0;     // Distance from water

        // Color
        ygl::vec4f color = INVALID_COLOR;

        // Diagram data
        const ygl::vec2f p;
        ygl::map<int, vcell*> touches;
        ygl::map<ygl::string, vertex*> adjacent;

        // Constructor
        vertex(const jcv_point& p) :
            id(make_id(get_vec2f(p))), p(get_vec2f(p)) {};
        vertex(const ygl::vec2f& p) :
            id(make_id(p)), p(p) {};
    };
    inline bool operator==(const vertex& v1, const vertex& v2) { return v1.id.compare(v2.id) == 0; }
    inline bool operator!=(const vertex& v1, const vertex& v2) { return v1.id.compare(v2.id) != 0; }
    inline bool operator<(const vertex& v1, const vertex& v2) { return v1.id.compare(v2.id); }

    struct vcell
    {
        // Cell ID
        const int id;

        // Relative 2D data
        bool border = false;   // The cells is at the map border

        // Y axis data
        float elevation = 0.0f; // Range [0.0f ; 1.0f]

        // Color
        ygl::vec4f color = INVALID_COLOR;

        // Diagram data
        const ygl::vec2f center;
        ygl::map<int, vcell*> neighbors;
        ygl::map<ygl::string, vertex*> vertices;
        ygl::vector<edge*> edges;

        // Constructor
        vcell(const jcv_site* s) :
            id(s->index), center(get_vec2f(s->p)) {};

        // Cleanup
        ~vcell()
        {
            for (auto e : edges)
                if (e) delete e;
        }
    };
    inline bool operator==(const vcell& c1, const vcell& c2) { return c1.id == c2.id; }
    inline bool operator!=(const vcell& c1, const vcell& c2) { return c1.id != c2.id; }
    inline bool operator<(const vcell& c1, const vcell& c2) { return c1.id < c2.id; }

    struct edge
    {
        // Diagram data
        vertex* v0;
        vertex* v1;
        vcell* d0;
        vcell* d1;

        // Constructors
        edge(vertex* v0, vertex* v1) :
            v0(v0), v1(v1), d0(nullptr), d1(nullptr) {};
        edge(vertex* v0, vertex* v1, vcell* d0, vcell* d1) :
            v0(v0), v1(v1), d0(d0), d1(d1) {};
    };
    inline bool operator==(const edge& e1, const edge& e2) { 
        return (e1.v0 == e2.v0 && e1.v1 == e2.v1) || (e1.v0 == e2.v1 && e1.v1 == e2.v0); 
    }
    inline bool operator!=(const edge& e1, const edge& e2) {
        return (e1.v0 != e2.v0 || e1.v1 != e2.v1) && (e1.v0 != e2.v1 || e1.v1 != e2.v0); 
    }

    /*
    -----------------------------------------------------------------------------
    Diagram Utils
    -----------------------------------------------------------------------------
    */

    template <typename K, typename V>
    void add_once(ygl::map<K, V*>& m, V* e)
    {
        // Add to the map only if it not contains the element
        if (m.find(e->id) == m.end())
            m[e->id] = e;
    }

    bool is_island(ygl::vec2f np, const map_options* opt)
    {
        /*
        Decide if a 2D normalized point (in the range [-1.0f, +1.0f]) is island or not.

        Adapted from: https://github.com/redblobgames/mapgen2/blob/master/water.js
        */

        auto distance = ygl::max(abs(np.x), abs(np.y));
        auto n = ygl::perlin_fbm_noise({ np.x, 0.0f, np.y }, opt->lacunarity, opt->gain, opt->octaves);
        n = ygl::lerp(n, 0.5f, opt->round);
        return n - (1.0f - opt->inflate) * distance * distance < 0.0f;
    }

    /*
    -----------------------------------------------------------------------------
    Biomes And Colors

    Adapted from https://github.com/amitp/mapgen2/blob/master/mapgen2.as
    -----------------------------------------------------------------------------
    */

    ygl::map<ygl::string, ygl::material*> colors = {
        // Features
        { "ocean", make_material("ocean",{ 68 / 255.0f, 68 / 255.0f, 112 / 255.0f }) },
        { "coast", make_material("coast",{ 51 / 255.0f, 51 / 255.0f, 90 / 255.0f }) },
        { "lakeshore", make_material("lakeshore",{ 34 / 255.0f, 85 / 255.0f, 136 / 255.0f }) },
        { "lake", make_material("lake",{ 51 / 255.0f, 102 / 255.0f, 153 / 255.0f }) },
        { "river", make_material("river",{ 34 / 255.0f, 85 / 255.0f, 163 / 255.0f }) },
        { "marsh", make_material("marsh",{ 47 / 255.0f, 102 / 255.0f, 102 / 255.0f }) },
        { "ice", make_material("ice",{ 153 / 255.0f, 255 / 255.0f, 255 / 255.0f }) },
        { "beach", make_material("beach",{ 160 / 255.0f, 144 / 255.0f, 119 / 255.0f }) },
        { "road1", make_material("road1",{ 68 / 255.0f, 34 / 255.0f, 17 / 255.0f }) },
        { "road2", make_material("road2",{ 85 / 255.0f, 51 / 255.0f, 34 / 255.0f }) },
        { "road3", make_material("road3",{ 102 / 255.0f, 68 / 255.0f, 51 / 255.0f }) },
        { "bridge", make_material("bridge",{ 104 / 255.0f, 104 / 255.0f, 96 / 255.0f }) },
        { "lava", make_material("lava",{ 204 / 255.0f, 51 / 255.0f, 51 / 255.0f }) },

        // Terrains
        { "snow", make_material("snow",{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f }) },
        { "tundra", make_material("tundra",{ 187 / 255.0f, 187 / 255.0f, 170 / 255.0f }) },
        { "bare", make_material("bare",{ 136 / 255.0f, 136 / 255.0f, 136 / 255.0f }) },
        { "scorched", make_material("scorched",{ 85 / 255.0f, 85 / 255.0f, 85 / 255.0f }) },
        { "taiga", make_material("taiga",{ 153 / 255.0f, 170 / 255.0f, 119 / 255.0f }) },
        { "shrubland", make_material("shrubland",{ 136 / 255.0f, 153 / 255.0f, 119 / 255.0f }) },
        { "temperate_desert", make_material("temperate_desert",{ 201 / 255.0f, 210 / 255.0f, 155 / 255.0f }) },
        { "temperate_rain_forest", make_material("temperate_rain_forest",{ 68 / 255.0f, 136 / 255.0f, 85 / 255.0f }) },
        { "temperate_deciduous_forest", make_material("temperate_deciduous_forest",{ 103 / 255.0f, 148 / 255.0f, 89 / 255.0f }) },
        { "grassland", make_material("grassland",{ 136 / 255.0f, 170 / 255.0f, 85 / 255.0f }) },
        { "subtropical_desert", make_material("grassland",{ 210 / 255.0f, 185 / 255.0f, 139 / 255.0f }) },
        { "tropical_rain_forest", make_material("tropical_rain_forest",{ 51 / 255.0f, 119 / 255.0f, 85 / 255.0f }) },
        { "tropical_seasonal_forest", make_material("tropical_seasonal_forest",{ 85 / 255.0f, 153 / 255.0f, 68 / 255.0f }) },

        // Base colors
        { "white", make_material("white",{ 1.0f, 1.0f, 1.0f }) },
        { "gray", make_material("gray",{ 0.2f, 0.2f, 0.2f }) },
        { "black", make_material("black",{ 0.0f, 0.0f, 0.0f }) },
        { "red", make_material("red",{ 1.0f, 0.0f, 0.0f }) },
        { "green", make_material("green",{ 0.0f, 1.0f, 0.0f }) },
        { "blue", make_material("blue",{ 0.0f, 0.0f, 1.0f }) },
        { "yellow", make_material("yellow",{ 1.0f, 1.0f, 0.0f }) },
    };

    ygl::string get_biome(vertex* v)
    {
        // Get biome by item properties
        
        if (v->lava)
        {
            return "lava";
        }
        else if (v->beach)
        {
            return "beach";
        }
        else if (v->water)
        {
            if(v->river) return "river";
            else if (v->shore) return "marsh";
            else if (v->ocean) return "lakeshore"; // Ocean color is bad
            else if (v->lake) return "lake";
            else if (v->elevation < 0.1f) return "marsh";
            else if (v->elevation > 0.8f) return "ice";
            else return "lake";
        }
        else if (v->elevation > 0.8f)
        {
            if (v->moisture > 0.50f) return "snow";
            else if (v->moisture > 0.33f) return "tundra";
            else if (v->moisture > 0.16f) return "bare";
            else return "scorched";
        }
        else if (v->elevation > 0.6f)
        {
            if (v->moisture > 0.66f) return "taiga";
            else if (v->moisture > 0.33f) return "shrubland";
            else return "temperate_desert";
        }
        else if (v->elevation > 0.3f)
        {
            if (v->moisture > 0.83f) return "temperate_rain_forest";
            else if (v->moisture > 0.50f) return "temperate_deciduous_forest";
            else if (v->moisture > 0.16f) return "grassland";
            else return "temperate_desert";
        }
        else
        {
            if (v->moisture > 0.66f) return "tropical_rain_forest";
            else if (v->moisture > 0.33f) return "tropical_seasonal_forest";
            else if (v->moisture > 0.16f) return "grassland";
            else return "subtropical_desert";
        }
    }

    ygl::material* get_material(ygl::string color_name)
    {
        if (colors.find(color_name) == colors.end())
            throw ygl::runtime_error("get_color: color not found");
        return colors[color_name];
    }

    ygl::vec4f get_color(ygl::string color_name)
    {
        if (colors.find(color_name) == colors.end())
            throw ygl::runtime_error("get_color: color not found");
        auto c = colors[color_name];
        return { c->kd.x, c->kd.y, c->kd.z, 1.0f };
    }

}

#endif