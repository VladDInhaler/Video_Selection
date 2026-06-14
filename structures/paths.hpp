//
// Created by admin on 06.06.26.
//

#ifndef PI_PROGRAMM_PATHS_HPP
#define PI_PROGRAMM_PATHS_HPP
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

inline std::string folder_path;

std::string load_default_video_file_path (std::string const folder_path) {

    std::string default_dir = folder_path + "/default";

    if (fs::exists(default_dir) && fs::is_directory(default_dir)) {
        for (const auto& entry : fs::directory_iterator(default_dir)) {
            if (entry.is_regular_file()) {
                return entry.path().string();
            }
        }

    }
    std::cout << "no proper default dir found" << std::endl;
    return "";
}



inline std::string input_pipe_path = "/dev/ttyACM0/";

//saves the paths for the video files
inline std::vector<std::string> video_file_paths = {
    // insert paths here like: /media/pi/NAME_DES_STICKS/path


};

//vector of vectors fo rfile paths
std::vector<std::vector<std::string>> easter_egg_Videos;
//first index is the  of the easter eggs
//second index is the strings of video file paths of each easter eggs


#endif //PI_PROGRAMM_PATHS_HPP