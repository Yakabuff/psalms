#include "play.h"
int playNote(char* note) {
   int keyNum = getKeyNumFromNotation(note); 
   int hz = getHertz(keyNum);
   float sine[TABLE_SIZE];
   PaStreamParameters outputParameters;
   PaStream *stream;
   PaError err;
   float buffer[FRAMES_PER_BUFFER][2]; /* stereo output buffer */
   int left_phase = 0;
   int right_phase = 0;
   int left_inc = 1;
   int right_inc = 3; /* higher pitch so we can distinguish left and right. */
   int i, j, k;
   int bufferCount;
   for( i=0; i<TABLE_SIZE; i++ )
   {
      sine[i] = (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. * hz );
   }
   printf("PortAudio Test: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);
   err = Pa_Initialize();
   if( err != paNoError ) goto error;

   outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
   if (outputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default output device.\n");
      goto error;
   }
   outputParameters.channelCount = 2;       /* stereo output */
   outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
   outputParameters.suggestedLatency = 0.050; // Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
   outputParameters.hostApiSpecificStreamInfo = NULL;

   err = Pa_OpenStream(
             &stream,
             NULL, /* no input */
             &outputParameters,
             SAMPLE_RATE,
             FRAMES_PER_BUFFER,
             paClipOff,      /* we won't output out of range samples so don't bother clipping them */
             NULL, /* no callback, use blocking API */
             NULL ); /* no callback, so no callback userData */
   if( err != paNoError ) goto error;
   err = Pa_StartStream( stream );
   if( err != paNoError ) goto error;
   printf("Play for %d seconds.\n", NUM_SECONDS );

   bufferCount = ((NUM_SECONDS * SAMPLE_RATE) / FRAMES_PER_BUFFER);

   for( i=0; i < bufferCount; i++ )
   {
      for( j=0; j < FRAMES_PER_BUFFER; j++ )
      {
      buffer[j][0] = sine[left_phase];  /* left */
      buffer[j][1] = sine[right_phase];  /* right */
      left_phase += left_inc;
      if( left_phase >= TABLE_SIZE ) left_phase -= TABLE_SIZE;
         right_phase += right_inc;
      if( right_phase >= TABLE_SIZE ) right_phase -= TABLE_SIZE;
      }

      err = Pa_WriteStream( stream, buffer, FRAMES_PER_BUFFER );
      if( err != paNoError ) goto error;
    }

    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    ++left_inc;
    ++right_inc;

    Pa_Sleep( 1000 );
    
error:
    fprintf( stderr, "An error occurred while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    // Print more information about the error.
    if( err == paUnanticipatedHostError )
    {
        const PaHostErrorInfo *hostErrorInfo = Pa_GetLastHostErrorInfo();
        fprintf( stderr, "Host API error = #%ld, hostApiType = %d\n", hostErrorInfo->errorCode, hostErrorInfo->hostApiType );
        fprintf( stderr, "Host API error = %s\n", hostErrorInfo->errorText );
    }
    Pa_Terminate();
    return err;
}

int getHertz(int key) {
   return 2^((key-49)/12) * 440;
}
