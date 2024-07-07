#ifndef GRID_INFO_HPP_
#define GRID_INFO_HPP_

#include <iostream>
#include <string>

struct GridInfo
{
  int x, y;
  GridInfo() : x(0), y(0)
  {
  }
  
  GridInfo(int x, int y) : x(x), y(y)
  {
  }

  friend bool operator==(const GridInfo& one, const GridInfo& other)
  {
    return one.x == other.x && one.y == other.y;
  }
  friend bool operator!=(const GridInfo& one, const GridInfo& other)
  {
    return !(one == other);
  }
  friend std::ostream& operator<<(std::ostream& os, const GridInfo& g)
  {
    os << g.x << "_" << g.y;
    return os;
  }
};

// This is for unordered_map and unodered_set
namespace std
{
template <>
struct hash<GridInfo>
{
public:
  size_t operator()(const GridInfo& grid) const
  {
    std::size_t seed = 0;
    seed ^= std::hash<int>{}(grid.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= std::hash<int>{}(grid.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};
}  // namespace std

template <typename PointT>
GridInfo pointToGrid(const PointT& p, double res_x, double res_y)
{
    int x_id = static_cast<int>(std::floor(p.x / res_x) * res_x);
    int y_id = static_cast<int>(std::floor(p.y / res_y) * res_y);

    return GridInfo(x_id, y_id);
}

#endif