#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "structures/paths.hpp"
#include "structures/data_structures.hpp"
#include "functions/start_programs.hpp"
#include "functions/load_functs.hpp"
#include "functions/play_functs.hpp"
#include "functions/config_functs.hpp"

//config.cfg must be set to the correct paths
//the first video to be added to the video direcorie will have the index 0 and will be played when dialing a 0
//the second vid tba will have index 1 and ongoing

//easter eggs are added by putting a subdirectory with a video in it, in the video directory
//the sub directories name will be the number to dial and then the video in thi dir is played



int main() {
    bool program_running = true;
    std::cout << "  program running" << std::endl;

    load_cfg (folder_path, input_pipe_path);
    std::string default_video_file_path = load_default_video_file_path(folder_path);

    load_videos_from_folder(folder_path, video_file_paths); //load the video files into the vector

    play_default(default_video_file_path);

    do {
        //std::string input = read_input2(input_pipe_path);

        std::string input;
        //if (std::cin.rdbuf()->in_avail() > 0 || std::getline(std::cin, input)) {
        if (std::getline(std::cin, input)) { //testing this right now


            std::cout << input << std::endl;

            if (input == "") { }

            //playing video if exists for the input
            else if (input.length() == 1 && std::isdigit(static_cast<unsigned char>(input[0]))) {
                int video_index = stoi(input); //converting input string to integer video index
                play_from_index(video_index, video_file_paths, default_video_file_path); //starting the function with the index of the user input
            }
            //playing hidden easter egg video if input matches their dir name
            else if (input.length() > 1 && std::isdigit(static_cast<unsigned char>(input[0]))) {
                try_easter_Eggs (easter_egg_Names, easter_egg_Videos, default_video_file_path, input);
            }
            //if not one of those inputs throw try again error phrase
            else if (input == "q" || input == "quit") {
                program_running = false;
            }
            else {
                std::cout << "  invalid input, please try again" << std::endl;

        }

 }

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    } while (program_running);

    std::system ("./kill_mpv.sh");
    //end of the program
    std::cout << "   quitting program" << std::endl;
    return 0;
}