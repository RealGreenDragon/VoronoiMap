
#include "voronoi.h"

int main(int argc, char** argv)
{
	// Init parser
    auto parser = ygl::make_parser(argc, argv, "Voronoi map generator", "Voronoi map generator");

    // Scene args
	auto scn_out = ygl::parse_opt<ygl::string>(parser, "--output", "-o", 
        "Path where save the OBJ scene (default: voronoi_map.obj)", "voronoi_map.obj");

    // Voronoi args
    auto map_side = ygl::parse_opt<float>(parser, "--map_side", "", 
        "Map side (minimum: 4.0, default 20.0)", 20.0f);
    auto max_elevation = ygl::parse_opt<float>(parser, "--max_elevation", "", 
        "Maximum map elevation (minimum: 0.0, default 1.0)", 1.0f);
	auto n_points = ygl::parse_opt<int>(parser, "--points", "", 
        "Voronoi points number (minimum: 1000, default: 2000)", 2000);
    auto n_relaxations = ygl::parse_opt<int>(parser, "--relaxations", "", 
        "Voronoi relaxations number (minimum: 2, default: 2)", 2);
    
    // Island args
    auto n_rivers = ygl::parse_opt<int>(parser, "--rivers", "", "rivers number (default: 4)", 4);
    auto island_regularity = ygl::parse_opt<float>(parser, "--island_regularity", "", 
        "How many the island seems a square (1.0 = square ; default: 0.5)", 0.5f);
    auto island_compactness = ygl::parse_opt<float>(parser, "--island_compactness", "", 
        "How many the island is compact (0.0 = one compact island ; default: 0.5)", 0.5f);
    auto island_proportion = ygl::parse_opt<float>(parser, "--island_proportion", "", 
        "How many the island fit the map (1.0 = fit all the map ; default: 0.4)", 0.4f);
    auto coast_compactness = ygl::parse_opt<float>(parser, "--coast_compactness", "", 
        "How many rocks around the coast (10.0 = more rocks ; default: 2.0)", 2.0f);
    auto coast_regularity = ygl::parse_opt<int>(parser, "--coast_regularity", "", 
        "How many the coast is jagged (10 = more jagged ; default: 6)", 6);

    // Check for errors
    if (ygl::should_exit(parser))
    {
        printf("Args error!\n");
        return 1;
    }

    // Init voronoi map
    auto voronoi_map = new voronoi::VoronoiMap(
        map_side, n_points, n_relaxations,
        new voronoi::map_options(
            island_regularity, island_compactness, island_proportion, coast_compactness, coast_regularity,
            max_elevation, 
            n_rivers
        )
    );

    // Generate scene
    auto scn = voronoi_map->generate_scene();

	// Save scene and free the memory
	printf("Saving scene %s\n", scn_out.c_str());
	ygl::save_scene(scn_out, scn, ygl::save_options{});
	delete scn;
    delete voronoi_map;

    return 0;
}