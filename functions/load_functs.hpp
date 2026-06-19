//
// Created by admin on 06.06.26.
//

#ifndef PI_PROGRAMM_LOAD_FUNCTS_HPP
#define PI_PROGRAMM_LOAD_FUNCTS_HPP
#include <filesystem>
#include <vector>
#include <fstream>
#include <algorithm>
#include <fcntl.h>
#include <map>
#include <unistd.h>

#include "../structures/paths.hpp"
#include "../structures/data_structures.hpp"


namespace fs = std::filesystem;

std::string read_input2(std::string const& input_pipe_path) {
    int fd = open(input_pipe_path.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd == -1) return "";

    char buffer[128];
    // Read liest die Pipe. bytes_read sagt uns exakt, wie viele Zeichen da sind.
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);

    if (bytes_read <= 0) return "";

    // String sauber beenden
    buffer[bytes_read] = '\0';
    std::string result(buffer);

    // EINFACHE BEREINIGUNG:
    // Wenn das letzte Zeichen ein Zeilenumbruch (\n oder \r) ist, schneide es ab.
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }

    return result;
}


std::string read_input (std::string const& input_pipe_path) {

    std::ifstream arduino_pipe(input_pipe_path);
    std::string input;
    std::string latest_input;
    if (arduino_pipe.is_open()) {
        while (std::getline(arduino_pipe, input )) {
            if (!input.empty()) {
                latest_input = input;
            }

        }

        arduino_pipe.close();
        return latest_input;
    }

    else {
        std::cout << " pipe not open " << std::endl;
        return ""; //fallback if connection is lost
    }
return "";
}




//load videos from folder into the vector
inline void load_videos_from_folder(const std::string &folder_path, std::vector<std::string> &video_file_paths) {
    //clear the vector
    video_file_paths.clear();

    try {
        if (fs::exists(folder_path) && fs::is_directory(folder_path)) {
            for (const auto &entry: fs::directory_iterator(folder_path)) {
                //
                //only take files no subdirectorys
                if (fs::is_regular_file(entry)) {
                    std::string path = entry.path().string();
                    auto ext = entry.path().extension().string();

                    if (ext == ".mp4" or ext == ".mkv") {
                        video_file_paths.push_back(path);
                    }
                }
            }
        }
        //sorting
        std::sort(video_file_paths.begin(), video_file_paths.end());
    } catch (const fs::filesystem_error &e) {
        std::cerr << "  directory error: " << e.what() << std::endl;
    }
}

inline void load_easter_Eggs(
    std::vector<std::vector<std::string> > &easter_egg_Videos,
    const std::string &folder_path, std::vector<std::string> &easter_eggs_Names) {
    static bool already_loaded = false; //no use yet. can be implemented when func gets calle din a loop

    //creating  containers for easter egg videos

    //a vector element of inner vector for each sub directory/easter egg
    //std::vector<std::string> easter_egg_Dir;

    //vector of vector for video file paths
    //std::vector<std::vector<std::string> > easter_egg_Videos;

    //vector to safe the easter eggs number


    //loop trough content of the folder path directory and look for sub dir
    for (const auto &dir_entry: fs::directory_iterator(folder_path)) {
        if (fs::is_directory(dir_entry)) {
            //for later perfectionising when everything works
            //std::vector <std::string> found_in_this_dir;
            //save the subdirectories name
            std::string dir_Name = dir_entry.path().filename().string();
            //save directory(easter egg) name in a vector
            easter_eggs_Names.push_back(dir_Name);
            std::cout << "found hidden easter egg: " << dir_Name << std::endl;
            //add empty vector to inner 2d vectors
            easter_egg_Videos.emplace_back();
            //loop through the sub directory files
            for (const auto &file_entry: fs::directory_iterator(dir_entry.path())) {
                //checking current file in the directory is a video
                if (fs::is_regular_file(file_entry)) {
                    std::string video_path = file_entry.path().string();
                    auto ext = file_entry.path().extension();

                    if (ext == ".mp4" or ext == ".mkv") {
                        //saving file path to the vector in the vector
                        easter_egg_Videos.back().emplace_back(std::move(video_path));
                        std::cout << easter_egg_Videos.back().back() << std::endl;
                    }
                }
            }
        }
    }
    already_loaded = true;
    std::cout << "easter eggs loaded" << std::endl;
}

inline void load_easter_eggs_map (std::string &folder_path, std::map<std::string, std::string> &easter_eggs) {
    for (const auto &dir_entry: fs::directory_iterator(folder_path)) { //loop trough sub dirs
        if (fs::is_directory(dir_entry)) {
            std::string temp_dir_Name = dir_entry.path().filename().string();
            for (const auto &file_entry : fs::directory_iterator(dir_entry.path())) { //loop trough videos of sub dir
                if (fs::is_regular_file(file_entry)) { //if file is mp4
                    //store temp_dir_name key in the map
                    //store in the map with the key of its director
                    std::string video_path = file_entry.path().string();
                    easter_eggs.insert({temp_dir_Name, video_path});
                }
            }
        }
    }
}


#endif //PI_PROGRAMM_LOAD_FUNCTS_HPP