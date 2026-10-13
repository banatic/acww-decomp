/* func_02037a40 @ 0x02037a40, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04, unk_08, unk_0C, unk_10, unk_14, unk_18, unk_1C, unk_20;
    u32 pad_24;
    u32 unk_28, unk_2C;
} Elem1; // 0x30 bytes

typedef struct {
    u32 unk_00;
    u32 unk_04;
} Elem2; // 8 bytes

typedef struct {
    Elem1 e1[31];
    Elem2 e2[9];
    u8 unk_618;
    u8 pad_619[3];
    u32 unk_61C, unk_620, unk_624, unk_628, unk_62C;
    u32 unk_630, unk_634, unk_638, unk_63C, unk_640;
} UnkStruct_02037a40;

void func_02037a40(UnkStruct_02037a40 *t)
{
    Elem1 *p1;
    Elem2 *p2;
    unsigned int i;

    p1 = t->e1;
    for (i = 0; i < 31; i++) {
        p1->unk_00 = 0xffff;
        p1->unk_04 = 0;
        p1->unk_08 = 0;
        p1->unk_0C = 0;
        p1->unk_14 = 0;
        p1->unk_18 = 0;
        p1->unk_1C = 0;
        p1->unk_10 = 0;
        p1->unk_20 = 0;
        p1->unk_28 = 0;
        p1->unk_2C = 0;
        p1++;
    }

    p2 = t->e2;
    for (i = 0; i < 9; i++) {
        p2->unk_00 = 0xffff;
        p2->unk_04 = 0;
        p2++;
    }

    t->unk_630 = 0;
    t->unk_634 = 0;
    t->unk_638 = 0;
    t->unk_63C = 0;
    t->unk_640 = 0;
    t->unk_618 = 0;
    t->unk_61C = 0;
    t->unk_620 = 0;
    t->unk_624 = 0;
    t->unk_628 = 0;
    t->unk_62C = 0;
}
