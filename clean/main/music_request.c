/* The requests of the music queue (music_request.h). */
#include "music_request.h"

#include "clean.h"

static_assert(sizeof(MusicRequest) == 0x1c, "request size");
static_assert(offsetof(MusicRequest, music_started) == 0x14, "request music started");
static_assert(offsetof(MusicRequest, timer) == 0x18, "request timer");

/* func_02037458: a running timer counted down; whether it ran out this frame. */
int MusicRequest_CountDown(MusicRequest *request)
{
    if (request->timer > 0) {
        request->timer--;
        return request->timer <= 0;
    }
    return 0;
}
CLEAN_AS(func_02037458, MusicRequest_CountDown)

/* func_02037470: `from` copied over `to`, which is cleared first. The bytes 0x06-0x07 and
 * 0x15-0x17 of `to` are left as they are. */
void MusicRequest_Copy(MusicRequest *to, const MusicRequest *from)
{
    MusicRequest_Clear(to);
    to->priority = from->priority;
    to->music = from->music;
    to->unk_08 = from->unk_08;
    to->unk_0c = from->unk_0c;
    to->unk_10 = from->unk_10;
    to->head_only = from->head_only;
    to->current = from->current;
    to->done = from->done;
    to->music_started = from->music_started;
    to->timer = from->timer;
}
CLEAN_AS(func_02037470, MusicRequest_Copy)

/* func_020374ac: the request cleared: the lowest priority, no music, every other field 0 (the
 * bytes 0x06-0x07 and 0x15-0x17 are left as they are). */
void MusicRequest_Clear(MusicRequest *request)
{
    request->priority = MUSIC_REQUEST_CLEARED_PRIORITY;
    request->music = MUSIC_NONE;
    request->unk_08 = 0;
    request->unk_0c = 0;
    request->unk_10 = 0;
    request->head_only = 0;
    request->current = 0;
    request->done = 0;
    request->music_started = 0;
    request->timer = 0;
}
CLEAN_AS(func_020374ac, MusicRequest_Clear)

/* func_020374cc: its destructor: nothing. */
void MusicRequest_Destruct(MusicRequest *request)
{
    (void) request;
}
CLEAN_AS(func_020374cc, MusicRequest_Destruct)

/* func_020374d0: a request made of a priority, a music, the words 0x0c and 0x08 and the byte
 * 0x10, the rest cleared. */
MusicRequest *MusicRequest_Make(MusicRequest *request, int priority, int music, int unk_0c, int unk_08, int unk_10)
{
    MusicRequest_Clear(request);
    request->priority = priority;
    request->music = (u16) music;
    request->unk_0c = unk_0c;
    request->unk_08 = unk_08;
    request->unk_10 = (u8) unk_10;
    return request;
}
CLEAN_AS(func_020374d0, MusicRequest_Make)

/* func_020374fc: its default constructor: the request cleared; the request's address. */
int MusicRequest_ConstructDefault(MusicRequest *request)
{
    MusicRequest_Clear(request);
    return (int) (uintptr_t) request;
}
CLEAN_AS(func_020374fc, MusicRequest_ConstructDefault)
