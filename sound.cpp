#include <thread>
#include "sound.h"

Sound::Sound() {
  // AUDIO SETTINGS
  memset(&format, 0, sizeof(format));
  format.bits = 16;
  format.channels = 1;
  format.rate = 44100;
  format.byte_format = AO_FMT_LITTLE;

  
    ao_initialize();
    int defaultDriver = ao_default_driver_id();
    device = ao_open_live(defaultDriver, &format, NULL);
    if(!device){
        std::cerr<<"Error: failed to open audio device"<<std::endl;
        exit(1);
    }

    bufferSize = format.bits/8 * format.channels * format.rate * (float)UPDATE_PERIOD_MS/1000;
    buffer = (char*)calloc(bufferSize, sizeof(char));
    if(!buffer){
        std::cerr<<"Error: could not allocate memory for buffer"<<std::endl;
        exit(1);
    }

    soundActive = true;
    soundPlaying = false;
    soundThread  = std::thread([this]{playLoop();}) 
}


