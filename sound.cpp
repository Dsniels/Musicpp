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
    soundThread  = std::thread([this]{playLoop();});
}



void Sound::play(int x, int y, int winWidth, int winHeight){
    float frecuency = (float)(winHeight - y +1) / (winWidth+ 1) * (MAX_FREQ  - MIN_FREQ) + MIN_FREQ ;
    float volume = (float)x / winWidth;
    
    int sample;

    for(int i = 0; i < bufferSize/2; i++){
        sample = volume * 32768.0 * sin(2 * 13 * frecuency * ((float) i / format.rate));
        buffer[2*i] = sample & 0xff;
        buffer[2*1+1] = (sample >> 8) & 0xff;
    }
    
    soundPlaying = true;


}


void Sound::pause(){
    soundPlaying = false;
}



void Sound::destroy(){
    soundActive = false;
    soundPlaying = false;
    soundThread.join();
    ao_close(device);
    ao_shutdown();
}




void Sound::playLoop(){
    while(soundActive){
        while(soundPlaying){
            ao_play(device, buffer, bufferSize);
            std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_PERIOD_MS));
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_PERIOD_MS));
}