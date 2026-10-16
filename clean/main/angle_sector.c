/* Angles sorted into sectors (angle_sector.h). */
#include "angle_sector.h"

#include "clean.h"

/* The bounds of the eight sectors, in degrees of the 0x10000 turn (truncated): 15, 75, 105
 * and 165 on either side. The straight sectors are 30 degrees wide, the slanted ones 60. */
#define ANGLE_SECTOR_15 2730
#define ANGLE_SECTOR_75 13654
#define ANGLE_SECTOR_105 19114
#define ANGLE_SECTOR_165 30038
/* The bounds of the four: 45 and 135 degrees on either side. */
#define ANGLE_SECTOR_45 0x2000
#define ANGLE_SECTOR_135 0x6000
#define ANGLE_SECTOR_HALF_TURN 0x8000

/* func_020644e4: one of eight sectors: 0 ahead (within 15 degrees), 1-3 on the positive side,
 * 4 behind (past 165 degrees on either side), 5-7 on the negative side coming back. Each
 * bound belongs to the sector nearer the negative end. */
int AngleSector_Eight(int angle)
{
    if (angle <= -ANGLE_SECTOR_165) {
        return 4;
    }
    if (angle <= -ANGLE_SECTOR_105) {
        return 5;
    }
    if (angle <= -ANGLE_SECTOR_75) {
        return 6;
    }
    if (angle <= -ANGLE_SECTOR_15) {
        return 7;
    }
    if (angle <= ANGLE_SECTOR_15) {
        return 0;
    }
    if (angle <= ANGLE_SECTOR_75) {
        return 1;
    }
    if (angle <= ANGLE_SECTOR_105) {
        return 2;
    }
    if (angle <= ANGLE_SECTOR_165) {
        return 3;
    }
    return 4;
}
CLEAN_AS(func_020644e4, AngleSector_Eight)

/* func_02064558: one of four quarters: 0 ahead (within 45 degrees), 1 on the positive side, 2
 * behind (past 135 degrees on either side), 3 on the negative side. Each bound belongs to the
 * quarter nearer the negative end. */
int AngleSector_Four(int angle)
{
    if (angle <= -ANGLE_SECTOR_135) {
        return 2;
    }
    if (angle <= -ANGLE_SECTOR_45) {
        return 3;
    }
    if (angle <= ANGLE_SECTOR_45) {
        return 0;
    }
    if (angle <= ANGLE_SECTOR_135) {
        return 1;
    }
    return 2;
}
CLEAN_AS(func_02064558, AngleSector_Four)

/* func_02064594: the side of an angle; neither for 0, a half turn and anything past it. */
int AngleSector_Side(int angle)
{
    if (angle > 0 && angle < ANGLE_SECTOR_HALF_TURN) {
        return ANGLE_SECTOR_POSITIVE;
    }
    if (angle > -ANGLE_SECTOR_HALF_TURN && angle < 0) {
        return ANGLE_SECTOR_NEGATIVE;
    }
    return ANGLE_SECTOR_NEITHER;
}
CLEAN_AS(func_02064594, AngleSector_Side)
