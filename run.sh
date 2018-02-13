
# For OSX and Linux

# Create scene
./bin/voronoi \
--output voronoi_map.obj \
--map_side 20.0 \
--max_elevation 2.0 \
--points 20000 \
--relaxations 50 \
--rivers 8 \
--island_regularity 0.2 \
--island_compactness 0.4 \
--island_proportion 0.3 \
--coast_compactness 2.0 \
--coast_regularity 6

# View scene
./bin/yitrace voronoi_map.obj -r 720
