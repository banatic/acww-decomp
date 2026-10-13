/* func_ov119_0229b188 @ 0x0229b188, 0xc0 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_02208098(void *p, int n);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov119_0229a410(void *p, int n);
extern int func_ov119_0229c608(void *p, int n);

typedef struct {
    u8 pad_00[0x9a];
    u16 unk_9A;
    u8 pad_9C;
    u8 unk_9D;
    u8 pad_9E[2];
    u8 unk_A0;
    u8 pad_A1[0x0f];
    u8 unk_B0;
    u8 unk_B1;
} State;

int func_ov119_0229b188(State *p)
{
    u8 v = p->unk_A0;

    if (v >= 14 && v <= 21) {
        if (func_ov119_0229c608(p, v - 14) != 0) {
            return 1;
        } else {
            return 0;
        }
    }
    if (v >= 8 && v <= 13) {
        u8 r = v - 8;
        if (r != p->unk_9D) {
            p->unk_9D = r;
            func_ov002_02208098(p, 14);
            if (r == 4) {
                RtcSendPxiCommand(0xf);
            } else {
                RtcSendPxiCommand(0xb);
            }
            return 1;
        } else {
            return 0;
        }
    }
    if (v == 22) {
        p->unk_B0 = 8;
        p->unk_B1 = 3;
        func_ov002_02208098(p, 8);
        RtcSendPxiCommand(0x2b);
        return 1;
    }
    if (v <= 7) {
        p->unk_9A = v;
        func_ov119_0229a410(p, 4);
        p->unk_B1 = 3;
        func_ov002_02208098(p, 8);
        RtcSendPxiCommand(0x2b);
        return 1;
    }
    return 0;
}
