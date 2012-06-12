#ifndef MICROTIME_H
#define MICROTIME_H

typedef unsigned long long mtime;

mtime microtime();

void microsleep(mtime time);

#endif

