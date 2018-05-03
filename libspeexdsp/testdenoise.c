#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "speex/speex_preprocess.h"
#include <stdio.h>

#define NN 320

int main()
{
   short in[NN];
   int i;
   SpeexPreprocessState *st;
   int count=0;
   float f;
   FILE *file_clean=NULL, *file_noise  =NULL;
   file_clean = fopen("G:\\pesq_test_sequences\\orginal_1_clean.pcm", "wb");
   file_noise = fopen("G:\\pesq_test_sequences\\orginal_1_addnoise.pcm", "rb");
   st = speex_preprocess_state_init(NN, 16000);
   i=1;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DENOISE, &i);
   i=0;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_AGC, &i);
   i=16000;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_AGC_LEVEL, &i);
   i=0;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB, &i);
   f=.0;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB_DECAY, &f);
   f=.0;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB_LEVEL, &f);
   while (1)
   {
      int vad,len;
      len = fread(in, sizeof(short), NN, file_noise);
	  if (len < NN)
		  break;
      if (feof(stdin))
         break;
      vad = speex_preprocess_run(st, in);
      /*fprintf (stderr, "%d\n", vad);*/
      fwrite(in, sizeof(short), NN, file_clean);
      count++;
   }
   fclose(file_noise);
   fclose(file_clean);
   speex_preprocess_state_destroy(st);
   return 0;
}
