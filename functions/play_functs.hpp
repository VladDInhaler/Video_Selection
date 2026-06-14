//
// Created by admin on 06.06.26.
//

#ifndef PI_PROGRAMM_PLAY_FUNCTS_HPP
#define PI_PROGRAMM_PLAY_FUNCTS_HPP
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "start_programs.hpp"
#include "../structures/data_structures.hpp"
#include "../structures/paths.hpp"

inline void play_from_index(int video_index, const std::vector<std::string>& video_path, const std::string& default_video_file_path) {
    try {
        //plays video depending on the value thats passed to the funtion

        std::string video = video_path.at(video_index);
        play_from_path(video, default_video_file_path);

        //index of the video in the container for the memory path
        std::cout << "playing " << video_file_paths.at(video_index) << std::endl;



    } catch (const std::out_of_range &e) {
        std::cerr << "index " << video_index << " doesnt exist!" << std::endl;
    }
}


inline void try_easter_Eggs(const std::vector<std::string> &easter_egg_Names, const std::vector<std::vector<std::string>> &easter_egg_Videos, auto input) {
    //loop through the vector of numbers
    for (int i = 0; i < easter_egg_Names.size(); i++) {
        //if input matches the content of the index then...
        if (input == easter_egg_Names[i]) {
            //call play function by giving it the path from the paths vektor with the same index
            //currently choosing the first video file to play so no random easter egg video so far
            play_from_path(input, easter_egg_Videos[i][0]);
        }
    }
}

#endif //PI_PROGRAMM_PLAY_FUNCTS_HPP