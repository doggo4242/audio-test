#include "snd.h"
#if defined(__linux__)
#include <pulse/simple.h>
#elif defined(_WIN32)
#include <stdio.h>
#include <windows.h>
#endif

int main(){
#if defined(_WIN32)
	FILE* fp = fopen("amogus.wav","wb");
	fwrite("RIFF",1,4,fp);
	uint32_t tmp32 = 36+sizeof(buf);
	fwrite(&tmp32,sizeof(tmp32),1,fp);
	fwrite("WAVEfmt ",1,8,fp);
	tmp32 = 16;
	fwrite(&tmp32,sizeof(tmp32),1,fp);
	uint16_t tmp16 = 3;
	fwrite(&tmp16,sizeof(tmp16),1,fp);
	tmp16 = 2;
	fwrite(&tmp16,sizeof(tmp16),1,fp);
	tmp32 = 48000;
	fwrite(&tmp32,sizeof(tmp32),1,fp);
	tmp32 = 48000*2*32/8;
	fwrite(&tmp32,sizeof(tmp32),1,fp);
	tmp16 = 2*32/8;
	fwrite(&tmp16,sizeof(tmp16),1,fp);
	tmp16 = 32;
	fwrite(&tmp16,sizeof(tmp16),1,fp);
	fwrite("data",1,4,fp);
	tmp32 = sizeof(buf);
	fwrite(&tmp32,sizeof(tmp32),1,fp);
	fwrite(buf,1,sizeof(buf),fp);
	fclose(fp);
	PlaySound(TEXT("amogus.wav"),NULL,SND_SYNC);
#elif defined(__linux__)
	pa_sample_spec spec;
	spec.format = PA_SAMPLE_FLOAT32LE;
	spec.channels = 2;
	spec.rate = 48000;
	pa_simple* p = pa_simple_new(NULL,"amogus",PA_STREAM_PLAYBACK,NULL,"amogus",&spec,NULL,NULL,NULL);
	pa_simple_write(p,buf,sizeof(buf),NULL);
	pa_simple_drain(p,NULL);
	pa_simple_free(p);
#endif
}
