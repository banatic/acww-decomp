/* func_02087500 @ 0x02087500, 0x1c6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02087500 {
    u8 pad_00[8]; // 0x00
    u16 unk_08;   // 0x08
    u8 data[14];  // 0x0a
    u8 unk_18;    // 0x18
};

extern int func_020644cc(int arg);
extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern u8 func_02087784(struct UnkStruct_02087500 *s);
extern u8 func_02087798(struct UnkStruct_02087500 *s);
extern u8 func_02087770(struct UnkStruct_02087500 *s);
extern u8 func_020876c8(struct UnkStruct_02087500 *s);
extern void func_020877ac(struct UnkStruct_02087500 *s, int a, int b);
extern void func_020876f0(struct UnkStruct_02087500 *s);

void func_02087500(struct UnkStruct_02087500 *s, int flag)
{
    if (s->unk_18 != 0xff) {
        int r = func_020644cc(0x65);
        switch (s->unk_18) {
            case 0:
                if (r < 0x1e) {
                    s->unk_18 = 1;
                } else if (r < 0x41) {
                    s->unk_18 = 3;
                } else if (r < 0x50) {
                    s->unk_18 = 2;
                }
                break;
            case 1:
                if (r < 0x14) {
                    s->unk_18 = 3;
                } else if (r < 0x41) {
                    s->unk_18 = 0;
                } else if (r < 0x55) {
                    s->unk_18 = 2;
                }
                break;
            case 2:
                if (r < 0x2d) {
                    s->unk_18 = 1;
                } else if (r < 0x46) {
                    s->unk_18 = 3;
                } else if (r < 0x5f) {
                    s->unk_18 = 0;
                }
                break;
            case 3:
                if (r < 0x19) {
                    s->unk_18 = 1;
                } else if (r < 0x46) {
                    s->unk_18 = 0;
                } else if (r < 0x55) {
                    s->unk_18 = 2;
                }
                break;
        }
        if (flag) {
            s->unk_18 = 2;
        }
    } else {
        s->unk_18 = func_020644cc(4);
    }

    s->unk_08 = 0;
    MI_CpuFill8(s->data, 0, 14);
    s->data[0] = func_020644cc(0x15) + 0x5a;
    s->data[1] = s->data[0];

    switch (s->unk_18) {
        case 0:
            s->data[2] = func_02087784(s);
            s->data[3] = func_02087798(s);
            s->data[4] = func_02087798(s);
            s->data[5] = func_02087798(s);
            s->data[6] = func_02087784(s);
            s->data[7] = func_02087784(s);
            s->data[8] = func_02087784(s);
            s->data[9] = func_02087798(s);
            s->data[10] = func_02087798(s);
            s->data[11] = func_02087784(s);
            s->data[12] = func_02087784(s);
            s->data[13] = func_02087784(s);
            break;
        case 1: {
            int index = func_020644cc(4) + 8;
            s->data[index] = func_020876c8(s);
            func_020877ac(s, 2, index - 2);
            s->data[index - 1] = func_02087770(s);
            s->data[index + 1] = func_02087770(s);
            s->data[index - 2] = func_02087784(s);
            s->data[index + 2] = func_02087784(s);
            func_020877ac(s, index + 3, 0xe);
            break;
        }
        case 2:
            func_020877ac(s, 2, 0xe);
            break;
        case 3:
            func_020876f0(s);
            break;
    }
}
