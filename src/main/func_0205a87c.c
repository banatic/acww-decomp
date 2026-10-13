/* func_0205a87c @ 0x0205a87c, 0x294 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern void MI_CpuFill8(void *, int, int);
extern unsigned short *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern int func_02053a88(unsigned short *);
extern int func_020539e4(unsigned short *);
extern int FX_Div(int, int);

int func_0205a87c(unsigned int *bounds, void *grid, int *primaryCategory, int *secondaryCategory)
{
    unsigned int primaryCount;
    unsigned int passA;
    unsigned int passB;
    unsigned short *primaryItem;
    unsigned short *secondaryItem;
    int secondaryDenominator;
    int secondaryAcreZ;
    int primaryDenominator;
    int highBonus;
    int primaryAcreZ;
    unsigned int secondaryCount;
    int primarySearchStart;
    int secondarySearchStart;
    unsigned short *primarySlot;
    unsigned short *secondarySlot;
    unsigned int secondaryIndex;
    unsigned int primaryIndex;
    int primaryId;
    int score;
    int primaryDistinct;
    int primaryLowBonus;
    unsigned int z;
    unsigned int x;
    int secondaryDistinct;
    int secondaryLowBonus;
    int secondaryId;
    unsigned int primarySearchIndex;
    unsigned int secondarySearchIndex;
    unsigned char primaryHistogram[3];
    unsigned char secondaryHistogram[3];
    unsigned short ids[24];

    MI_CpuFill8(primaryHistogram, 0, 3);
    MI_CpuFill8(secondaryHistogram, 0, 3);
    for (primarySearchIndex = 0; primarySearchIndex < 0x18; primarySearchIndex++) {
        ids[primarySearchIndex] = 0xffff;
    }
    // The ID table is cleared twice, with score initialized in between.
    score = 0;
    for (primarySearchIndex = score; primarySearchIndex < 0x18; primarySearchIndex++) {
        ids[primarySearchIndex] = 0xffff;
    }
    primaryCount = 0;
    passA = 0;
    primarySearchStart = 0;

    for (;;) {
        for (z = bounds[1]; z <= (unsigned int) bounds[3]; z++) {
            x = bounds[0];
            if (x > (unsigned int) bounds[2]) {
                continue;
            }
            primaryAcreZ = (int) z >> 4;
            for (; x <= (unsigned int) bounds[2]; x++) {
                int cx = (int) x >> 4;
                primaryItem = func_0204f5e0(grid, cx, primaryAcreZ, (int) (x - ((unsigned int) cx << 4)),
                                            (int) (z - ((unsigned int) primaryAcreZ << 4)), passA);
                if (primaryItem == 0) {
                    goto nextx;
                }
                if (func_0204bcdc(primaryItem) == 0) {
                    goto nextx;
                }
                primaryId = func_0204bc64(primaryItem);
                for (primarySearchIndex = primarySearchStart; primarySearchIndex < 0x18; primarySearchIndex++) {
                    primarySlot = &ids[primarySearchIndex];
                    if (primaryId == ids[primarySearchIndex]) {
                        break;
                    }
                    if (ids[primarySearchIndex] != 0xffff) {
                        continue;
                    }
                    *primarySlot = primaryId;
                    break;
                }
                primaryHistogram[func_02053a88(primaryItem)]++;
                primaryCount++;
            nextx:;
            }
        }
        passA = (unsigned char) (passA + 1);
        if (passA < 2) {
            continue;
        }
        break;
    }
    if (primaryCount >= 0xa) {
        primaryDistinct = 0;
        for (primarySearchIndex = 0; primarySearchIndex < 0x18; primarySearchIndex++) {
            if (ids[primarySearchIndex] != 0xffff) {
                primaryDistinct++;
            }
        }
        // The index is initialized before the loop-invariant score terms.
        primaryIndex = 0;
        primaryDenominator = primaryCount << 0xc;
        highBonus = primaryDistinct * 300;
        primaryLowBonus = primaryDistinct * 100;
        for (; primaryIndex < 3; primaryIndex++) {
            int fx;
            if (primaryIndex == 0) {
                continue;
            }
            fx = FX_Div((int) primaryHistogram[primaryIndex] << 0xc, primaryDenominator);
            if (fx >= 0xe66) {
                *primaryCategory = primaryIndex;
                score += highBonus;
            } else if (fx >= 0xb33) {
                *primaryCategory = primaryIndex;
                score += primaryLowBonus;
            }
        }
    }
    for (primarySearchIndex = 0; primarySearchIndex < 0x18; primarySearchIndex++) {
        ids[primarySearchIndex] = 0xffff;
    }
    secondaryCount = 0;
    passB = 0;
    secondarySearchStart = 0;

    for (;;) {
        for (z = bounds[1]; z <= (unsigned int) bounds[3]; z++) {
            x = bounds[0];
            if (x > (unsigned int) bounds[2]) {
                continue;
            }
            secondaryAcreZ = (int) z >> 4;
            for (; x <= (unsigned int) bounds[2]; x++) {
                int cx = (int) x >> 4;
                secondaryItem = func_0204f5e0(grid, cx, secondaryAcreZ, (int) (x - ((unsigned int) cx << 4)),
                                              (int) (z - ((unsigned int) secondaryAcreZ << 4)), passB);
                if (secondaryItem == 0) {
                    goto nextx2;
                }
                if (func_0204bcdc(secondaryItem) == 0) {
                    goto nextx2;
                }
                secondaryId = func_0204bc64(secondaryItem);
                for (secondarySearchIndex = secondarySearchStart; secondarySearchIndex < 0x18; secondarySearchIndex++) {
                    secondarySlot = &ids[secondarySearchIndex];
                    if (secondaryId == ids[secondarySearchIndex]) {
                        break;
                    }
                    if (ids[secondarySearchIndex] != 0xffff) {
                        continue;
                    }
                    *secondarySlot = secondaryId;
                    break;
                }
                secondaryHistogram[func_020539e4(secondaryItem)]++;
                secondaryCount++;
            nextx2:;
            }
        }
        passB = (unsigned char) (passB + 1);
        if (passB < 2) {
            continue;
        }
        break;
    }
    if (secondaryCount >= 0xa) {
        secondaryDistinct = 0;
        for (secondarySearchIndex = 0; secondarySearchIndex < 0x18; secondarySearchIndex++) {
            if (ids[secondarySearchIndex] != 0xffff) {
                secondaryDistinct++;
            }
        }
        secondaryIndex = 0;
        secondaryDenominator = secondaryCount << 0xc;
        highBonus = secondaryDistinct * 300;
        secondaryLowBonus = secondaryDistinct * 100;
        for (; secondaryIndex < 3; secondaryIndex++) {
            int fx;
            if (secondaryIndex == 0) {
                continue;
            }
            fx = FX_Div((int) secondaryHistogram[secondaryIndex] << 0xc, secondaryDenominator);
            if (fx >= 0xe66) {
                *secondaryCategory = secondaryIndex;
                score += highBonus;
            } else if (fx >= 0xb33) {
                *secondaryCategory = secondaryIndex;
                score += secondaryLowBonus;
            }
        }
    }
    return score;
}
