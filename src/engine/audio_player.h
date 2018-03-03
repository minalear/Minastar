//
// Created by Trevor Fisher on 3/3/2018.
//

#ifndef SINISTAR_AUDIO_PLAYER_H
#define SINISTAR_AUDIO_PLAYER_H

#include <string>
#include <unordered_map>
#include "irrKlang.h"

namespace minalear {
    class audio_player {
    private:
        irrklang::ISoundEngine *engine;
        std::unordered_map<std::string, irrklang::ISoundSource*> sound_library;

    public:
        audio_player();
        ~audio_player();

        void register_audio_file(const std::string name, const std::string path);
        void play_sound_effect(const std::string name);

        void play_song(const std::string name, bool loop);
        void stop_song(const std::string name);
    };

    extern audio_player audio_engine;
}

#endif //SINISTAR_AUDIO_PLAYER_H
