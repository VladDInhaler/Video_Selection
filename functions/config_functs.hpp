//
// Created by admin on 09.06.26.
//

#ifndef PI_PROGRAMM_CONFIG_FUNCTS_HPP
#define PI_PROGRAMM_CONFIG_FUNCTS_HPP

#include <fstream>
#include <iostream>
#include <string>

void load_cfg(std::string& folder_path, std::string& input_pipe_path) {

    std::ifstream config_file("config.cfg");

    if (config_file.is_open()) {
        std::string line;
        while (std::getline(config_file, line)) {
            size_t delimiter_pos = line.find('=');
            if (delimiter_pos != std::string::npos) {
                std::string key = line.substr(0, delimiter_pos);
                std::string value = line.substr(delimiter_pos + 1);
                if (key == "INPUT_PIPE_PATH") {
                    input_pipe_path = value;
                    std::cout << "input_pipe_path set to: " << input_pipe_path << std::endl;
                }
                else if (key == "VIDEO_DIRECTORY") {
                    folder_path = value;
                    std::cout << "video_dir_path set to: " <<  folder_path << std::endl;
                }
                else {
                    std::cerr << key << " is not a valid config variable." << std::endl;
                }

            }
        }
    }

}


#endif //PI_PROGRAMM_CONFIG_FUNCTS_HPP