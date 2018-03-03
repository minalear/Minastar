//
// Created by Trevor Fisher on 3/3/2018.
//

#include "audio_player.h"

using namespace minalear;
using namespace irrklang;

audio_player minalear::audio_engine;
audio_player::audio_player() {
    engine = createIrrKlangDevice();
}
audio_player::~audio_player() {
    engine->drop();
}

void audio_player::register_audio_file(const std::string name, const std::string path) {
    ISoundSource *sound_source = engine->addSoundSourceFromFile(path.c_str(),  E_STREAM_MODE::ESM_AUTO_DETECT, true);
    sound_library.insert({name, sound_source});
}
void audio_player::play_sound_effect(const std::string name) {
    engine->play2D(sound_library[name]);
}

void audio_player::play_song(const std::string name, bool loop) {
    engine->play2D(sound_library[name], loop);
}
void audio_player::stop_song(const std::string name) {
    engine->stopAllSoundsOfSoundSource(sound_library[name]);
}