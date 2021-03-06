#include "snd.h"
#if defined(_WIN32)
#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#elif defined(__linux__)
#include <pulse/simple.h>
#endif

int main(){
#if defined(_WIN32)
	FILE* fp = fopen("amogus.wav","wb");
	unsigned char header[] = {82,73,70,70,100,226,168,1,87,65,86,69,102,109,116,32,16,0,0,0,3,0,2,0,128,187,0,0,0,220,5,0,8,0,32,0,100,97,116,97,64,226,168,1,};
	fwrite(header,1,sizeof(header),fp);
	fwrite(buf,1,sizeof(buf),fp);
	fclose(fp);
	PlaySound(TEXT("amogus.wav"),NULL,SND_SYNC);
	remove("amogus.wav");
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
