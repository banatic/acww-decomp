/* The New Year's countdown as heard indoors: a process of overlay 4 (class vtable 0x02255b7c on
 * the Process base, 0x54 bytes) that, in the scenes the table data_ov004_022478f0 marks, plays
 * the countdown's sounds on 31 December as the seconds to midnight go by: 0x62 when one minute
 * is left, then each second 0x62 down to eleven seconds left and 0x60 for the last ten (0x61
 * at none left, which the clock never shows), and 0x61 once at 0:00:00 on 1 January.
 * Overlay 3's countdown board (ov003/countdown.h) plays the same sounds outdoors.
 *
 * Sounds go by changes of the seconds' last digit; the first change in the last hour after the
 * process is made is silent. */
#ifndef CLEAN_OV004_INDOOR_COUNTDOWN_H
#define CLEAN_OV004_INDOOR_COUNTDOWN_H

#include "autoload_2/process.h"
#include "types.h"

typedef struct IndoorCountdown {
    Process base;
    u8 last_digit; /* 0x50: the seconds' last digit last frame */
    u8 digit;      /* 0x51: this frame's */
    u8 silent;     /* 0x52: the next change plays nothing (set at the creation) */
    u8 new_year;   /* 0x53: the new year's sound was played */
} IndoorCountdown;

int IndoorCountdown_Execute(IndoorCountdown *self);
int IndoorCountdown_Create(IndoorCountdown *self);
IndoorCountdown *IndoorCountdown_Delete(IndoorCountdown *self);
IndoorCountdown *IndoorCountdown_Destruct(IndoorCountdown *self);
IndoorCountdown *IndoorCountdown_Construct(IndoorCountdown *self);
void IndoorCountdown_New(void);

#endif
