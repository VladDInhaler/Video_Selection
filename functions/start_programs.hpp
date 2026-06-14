//
// Created by admin on 06.06.26.
//

#ifndef PI_PROGRAMM_MPC_FUNC_HPP
#define PI_PROGRAMM_MPC_FUNC_HPP
#include <string>


inline void play_default (std::string const& default_video) {

    std::string cmd = "./kill_mpv.sh";
    //std::system (cmd.c_str());
    std::cout << "play_default_video\n";
    cmd = "./start_loop.sh " + default_video + " &";
    std::system (cmd.c_str());
}

inline void play_from_path (std::string const& video_path, std::string const& default_video) {
    std::string cmd = "./kill_mpv.sh";
    //std::system (cmd.c_str());
    std::cout << "play_video_path\n";
    cmd = "./play_from_path.sh " + video_path + " " + default_video + " &";
    std::system (cmd.c_str());
}
#endif //PI_PROGRAMM_MPC_FUNC_HPP