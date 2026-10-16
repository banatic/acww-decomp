/* The requests of the music queue (music_queue.h): reset, copy, construction and the countdown
 * of their timer. */
#ifndef CLEAN_MAIN_MUSIC_REQUEST_H
#define CLEAN_MAIN_MUSIC_REQUEST_H

#include "music_queue.h"
#include "types.h"

/* The priority of a cleared request, below every one asked for. */
#define MUSIC_REQUEST_CLEARED_PRIORITY 0x25

int MusicRequest_CountDown(MusicRequest *request);
void MusicRequest_Copy(MusicRequest *to, const MusicRequest *from);
void MusicRequest_Clear(MusicRequest *request);
void MusicRequest_Destruct(MusicRequest *request);
MusicRequest *MusicRequest_Make(MusicRequest *request, int priority, int music, int unk_0c, int unk_08, int unk_10);
int MusicRequest_ConstructDefault(MusicRequest *request);

#endif
