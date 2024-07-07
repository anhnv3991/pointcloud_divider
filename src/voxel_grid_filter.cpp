#include <unordered_map>

#include <pointcloud_divider/voxel_grid_filter.hpp>
#include <pointcloud_divider/grid_info.hpp>
#include <pointcloud_divider/centroid.hpp>

template <typename PointT>
void VoxelGridFilter<PointT>::filter(const PclCloudType & input, PclCloudType & output)
{
    if (resolution_ <= 0)
    {
        return;
    }

    std::unordered_map<GridInfo, Centroid<PointT>> grid_map;

    for (auto & p : input)
    {
        GridInfo gkey = pointToGrid(p, resolution_, resolution_);

        grid_map[gkey].add(p);
    }

    // Extract centroids
    output.reserve(grid_map.size());

    for (auto & it : grid_map)
    {
        output.push_back(it.second.get());
    }
}