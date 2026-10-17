/* The New Year's countdown heard indoors (indoor_countdown.h). */
#include "indoor_countdown.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/scene_query.h"
#include "main/sound.h"

static_assert(sizeof(IndoorCountdown) == 0x54, "indoor countdown");

/* The class and the process base's. */
extern const u32 data_ov004_02255b7c[];
extern const u32 data_020da13c[];

/* Whether each scene (0 to 0x32) hears the countdown. */
extern const u8 data_ov004_022478f0[];
#define INDOOR_COUNTDOWN_SCENES 0x33

/* The sounds. */
#define INDOOR_COUNTDOWN_SE_LAST_TEN 0x60
#define INDOOR_COUNTDOWN_SE_NEW_YEAR 0x61
#define INDOOR_COUNTDOWN_SE_SECOND 0x62
/* The seconds left from which INDOOR_COUNTDOWN_SE_LAST_TEN plays. */
#define INDOOR_COUNTDOWN_LAST_SECONDS 10

#define INDOOR_COUNTDOWN_SECONDS_PER_DAY 86400u
#define INDOOR_COUNTDOWN_SECONDS_PER_HOUR 3600u
#define INDOOR_COUNTDOWN_SECONDS_PER_MINUTE 60u

static void IndoorCountdown_play(const IndoorCountdown *self, int number)
{
    if (self->silent == 0) {
        SoundSys_PlaySe(number);
    }
}

/* func_ov004_02233334 (vtable slot 6, each frame): see indoor_countdown.h. Done.
 * QUIRK: the seconds left are worked out in unsigned arithmetic from the clock's fields as
 * they are, without checking them. */
int IndoorCountdown_Execute(IndoorCountdown *self)
{
    u8 scene = SceneQuery_Current();
    DateTime now = {0};
    DateTime_Now(&now);
    if (scene >= INDOOR_COUNTDOWN_SCENES || data_ov004_022478f0[scene] == 0) {
        return 1;
    }

    if (now.month == 12 && now.day == 31) {
        u32 left =
            INDOOR_COUNTDOWN_SECONDS_PER_DAY - (u32) (now.second + now.minute * (int) INDOOR_COUNTDOWN_SECONDS_PER_MINUTE +
                                                      now.hour * (int) INDOOR_COUNTDOWN_SECONDS_PER_HOUR);
        u32 hours = left / INDOOR_COUNTDOWN_SECONDS_PER_HOUR;
        left -= hours * INDOOR_COUNTDOWN_SECONDS_PER_HOUR;
        u32 minutes = left / INDOOR_COUNTDOWN_SECONDS_PER_MINUTE;
        u32 seconds = left - minutes * INDOOR_COUNTDOWN_SECONDS_PER_MINUTE;
        self->digit = (u8) (seconds % 10);
        if (self->digit != self->last_digit && hours == 0) {
            if (minutes == 1 && seconds == 0) {
                IndoorCountdown_play(self, INDOOR_COUNTDOWN_SE_SECOND);
            } else if (minutes == 0) {
                if (seconds == 0) {
                    IndoorCountdown_play(self, INDOOR_COUNTDOWN_SE_NEW_YEAR);
                } else if (seconds <= INDOOR_COUNTDOWN_LAST_SECONDS) {
                    IndoorCountdown_play(self, INDOOR_COUNTDOWN_SE_LAST_TEN);
                } else {
                    IndoorCountdown_play(self, INDOOR_COUNTDOWN_SE_SECOND);
                }
            }
            self->silent = 0;
        }
        self->last_digit = self->digit;
    } else if (now.month == 1 && now.day == 1 && now.hour == 0 && now.minute == 0 && now.second == 0) {
        if (self->new_year == 0) {
            SoundSys_PlaySe(INDOOR_COUNTDOWN_SE_NEW_YEAR);
            self->new_year = 1;
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02233334, IndoorCountdown_Execute)

/* func_ov004_0223347c (vtable slot 0, the creation): the next change is silent. Done. */
int IndoorCountdown_Create(IndoorCountdown *self)
{
    self->silent = 1;
    return 1;
}
CLEAN_AS(func_ov004_0223347c, IndoorCountdown_Create)

/* func_ov004_02233488 (the deleting destructor, vtable slot 0x44) */
IndoorCountdown *IndoorCountdown_Delete(IndoorCountdown *self)
{
    self->base.vtable = data_ov004_02255b7c;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02233488, IndoorCountdown_Delete)

/* func_ov004_022334b0 (the destructor, vtable slot 0x40) */
IndoorCountdown *IndoorCountdown_Destruct(IndoorCountdown *self)
{
    self->base.vtable = data_ov004_02255b7c;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov004_022334b0, IndoorCountdown_Destruct)

/* func_ov004_022334d0 (the constructor): the base's vtable set before the class's. */
IndoorCountdown *IndoorCountdown_Construct(IndoorCountdown *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov004_02255b7c;
    return self;
}
CLEAN_AS(func_ov004_022334d0, IndoorCountdown_Construct)

/* func_ov004_022334f0 (the profile's maker): a new one from the room's heap; nothing when it
 * has no room. */
void IndoorCountdown_New(void)
{
    IndoorCountdown *self = Heap_AllocAuxZeroed(sizeof(IndoorCountdown));
    if (self != NULL) {
        IndoorCountdown_Construct(self);
    }
}
CLEAN_AS(func_ov004_022334f0, IndoorCountdown_New)
