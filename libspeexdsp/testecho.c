#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "speex/speex_echo.h"
#include "speex/speex_preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define NN 128
#define TAIL 1024

int main(int argc, char **argv)
{
   FILE *echo_fd=NULL, *ref_fd=NULL, *e_fd=NULL;
   short echo_buf[NN], ref_buf[NN], e_buf[NN];
   SpeexEchoState *st;
   SpeexPreprocessState *den;
   int sampleRate = 8000;

   /*if (argc != 4)
   {
      fprintf(stderr, "testecho mic_signal.sw speaker_signal.sw output.sw\n");
      exit(1);
   }*/
   echo_fd = fopen("G:\\ASP≤‚ ‘\\818_echo_testing\\Debug_data20160818162405\\nearend_in.pcm", "rb");
   ref_fd  = fopen("G:\\ASP≤‚ ‘\\818_echo_testing\\Debug_data20160818162405\\farend_in.pcm",  "rb");
   e_fd    = fopen("G:\\ASP≤‚ ‘\\818_echo_testing\\Debug_data20160818162405\\nearend_hao.pcm", "wb");

   st = speex_echo_state_init(NN, TAIL);
   den = speex_preprocess_state_init(NN, sampleRate);
   speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
   speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);

   while (!feof(ref_fd) && !feof(echo_fd))
   {
      fread(ref_buf, sizeof(short), NN, ref_fd);
      fread(echo_buf, sizeof(short), NN, echo_fd);
      speex_echo_cancellation(st, ref_buf, echo_buf, e_buf);
      speex_preprocess_run(den, e_buf);
      fwrite(e_buf, sizeof(short), NN, e_fd);
   }
   speex_echo_state_destroy(st);
   speex_preprocess_state_destroy(den);
   fclose(e_fd);
   fclose(echo_fd);
   fclose(ref_fd);
   return 0;
}
