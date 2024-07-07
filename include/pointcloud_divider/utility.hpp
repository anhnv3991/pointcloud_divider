#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>

namespace util
{
// Create a directory
inline bool make_dir(const std::string & path)
{
    std::string cmd = "mkdir -p " + path;
    std::string err_msg = "Error: Failed to execute command " + cmd;

    if (std::system(cmd.c_str()))
    {
        perror(err_msg.c_str());
        exit(EXIT_FAILURE);
    }

    return true;
}

// Remove a file/directory at @path
inline bool remove(const std::string & path)
{
    if (!std::filesystem::remove_all(path))
    {
        std::cerr << "Error: File at " << path << " does not exist." << std::endl;
        return false;
    }

    return true;
}

// Parse the name of the PCD file, and return the number of points in the file
size_t point_num(const std::string & pcd_path)
{
    // Get the file name only
    auto last_ubar_pos = pcd_path.rfind("_");
    auto last_dot_pos = pcd_path.rfind(".");
    auto pnum_str = pcd_path.substr(last_ubar_pos + 1, last_dot_pos - last_ubar_pos - 1);

    return std::stoi(pnum_str);
}

}

#endif