/* An angle (0x10000 a full turn, -0x8000 to 0x8000 either side of ahead) sorted into sectors:
 * eight, four or two of them, numbered from ahead (0) towards the positive side. */
#ifndef CLEAN_MAIN_ANGLE_SECTOR_H
#define CLEAN_MAIN_ANGLE_SECTOR_H

#include "types.h"

/* The two sides AngleSector_Side tells. */
enum AngleSectorSide {
    ANGLE_SECTOR_POSITIVE = 0,
    ANGLE_SECTOR_NEGATIVE = 1,
    ANGLE_SECTOR_NEITHER = 2, /* straight ahead or behind */
};

int AngleSector_Eight(int angle);
int AngleSector_Four(int angle);
int AngleSector_Side(int angle);

#endif
