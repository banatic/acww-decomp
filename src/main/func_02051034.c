/* func_02051034 @ 0x02051034, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x34];
    u32 unk_34;
    char pad_38[0x30];
    u32 unk_68;
} UnkStruct_02051034;

extern u8 data_021c8344[];

extern int func_02050ef4(UnkStruct_02051034 *s);
extern int func_02050edc(UnkStruct_02051034 *s);
extern int func_02050e74(UnkStruct_02051034 *s);

void func_02051034(UnkStruct_02051034 *s)
{
    int v;
    int hi;
    unsigned int y;
    int yy;
    u32 x;
    u32 col;
    u32 off;
    u32 j;
    u8 *p;

    if (func_02050ef4(s) == 0 && func_02050edc(s) == 0) {
        return;
    }
    v = func_02050e74(s);
    y = 0;
    hi = v << 4;
    for (; y < 8; y++) {
        j = 0;
        yy = y * 8;
        for (; j < s->unk_34; j++) {
            x = s->unk_68 + j;
            col = x >> 3;
            off = (u32) (yy + (int) (x - col * 8)) >> 1;
            if (col < 0x20) {
                p = data_021c8344 + col * 32 + off;
                if ((x & 1) != 0) {
                    *p &= ~0xf0;
                    *p |= (u8) hi;
                } else {
                    *p &= ~0x0f;
                    *p |= (u8) v;
                }
            }
        }
    }
}
