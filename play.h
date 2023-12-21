#include <portaudio.h>
#include "keys.h"
#include <math.h>
#define TABLE_SIZE   (200)
#ifndef M_PI
#define M_PI  (3.14159265)
#endif
#define SAMPLE_RATE         (44100)
#define FRAMES_PER_BUFFER   (1024)
#define NUM_SECONDS         (5)
int playNote(char* note);
int getHertz(int key);
