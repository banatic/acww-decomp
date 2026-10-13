/* func_ov046_02261508 @ 0x02261508, 0x88 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b;
} UnkStruct_02261508;

extern int data_ov046_0226245c;
extern UnkStruct_02261508 data_ov046_02262464[];
extern UnkStruct_02261508 data_ov046_02261f98;
extern UnkStruct_02261508 data_ov046_02261f90;
extern UnkStruct_02261508 data_ov046_02261f28;
extern UnkStruct_02261508 data_ov046_02261f58;
extern UnkStruct_02261508 data_ov046_02261f68;

void func_ov046_02261508(u8 *self, int i)
{
    if ((data_ov046_0226245c & 1) == 0) {
        data_ov046_02262464[0] = data_ov046_02261f98;
        data_ov046_02262464[1] = data_ov046_02261f90;
        data_ov046_02262464[2] = data_ov046_02261f28;
        data_ov046_02262464[3] = data_ov046_02261f58;
        data_ov046_02262464[4] = data_ov046_02261f68;
        data_ov046_0226245c |= 1;
    }
    *(UnkStruct_02261508 *) (self + 0xb8) = data_ov046_02262464[i];
}
