#include "microtime.h"
#include <sys/timeb.h>
#include <unistd.h>

static time_t last_time = 0;

mtime microtime()
{
	struct timeb tp;

	ftime(&tp);
	if (last_time == 0) last_time = tp.time;

	return ((mtime)(tp.time - last_time)) * 1000 + (mtime)tp.millitm;
}

void microsleep(mtime time)
{
	usleep(time * 1000);
}

