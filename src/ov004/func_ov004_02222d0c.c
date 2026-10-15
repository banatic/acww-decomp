/* func_ov004_02222d0c @ 0x02222d0c, 0x1b4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    unsigned char kind : 2, row : 3, column : 3;
} Bits;
typedef struct {
    u8 base;
    u8 pad_01[3];
    int count;
} Choice;
typedef struct {
    void *text;
    u8 message;
} Output;
#define P(p, o) (*(u8 **) ((p) + (o)))
extern u8 *data_020ccf94;
extern u8 data_ov004_022476dc[][7], data_ov004_022476d4[];
extern Choice data_ov004_022476f8[];
extern void *data_ov004_02254338[];
extern unsigned func_ov004_02222b3c(void *receiver);
extern int func_02073d90(void *), func_020a12e8(void), func_0202ea40(void *, void *, int), func_0202ea80(int, int),
    func_0209ded0(void), func_020644cc(int);
extern short *func_0209d358(int, int);
extern void func_0202ea28(void *, void *), func_020160d8(void *, void *);
extern void *func_02082644(int);
void func_ov004_02222d0c(u8 *self, Output *out)
{
    u8 packed[4];
    unsigned kind = func_ov004_02222b3c(P(self, 0xb0));
    u8 *world = data_020ccf94;
    if (func_02073d90(world) || *func_0209d358(0, 0x4a) != 0) {
        kind = 0;
        out->message = 0x57;
    } else if (func_020a12e8()) {
        kind = 2;
        out->message = 5;
    } else if (func_0202ea40(P(self, 0xb0), packed, 2)) {
        kind = 1;
        P(self, 0xb0)[0x70e] = 1;
        out->message = data_ov004_022476dc[((Bits *) packed)->row][((Bits *) packed)->column];
        func_0202ea28(P(self, 0xb0), packed);
    } else if (!func_0202ea80(0x10, 1)) {
        if (kind >= 12) {
            out->message = data_ov004_022476d4[func_0209ded0()];
        } else {
            out->message = data_ov004_022476f8[kind].base;
        }
        kind = 0;
    } else {
        if (kind > 12) {
            out->message = func_020644cc(5) + 40;
        } else {
            int idx = kind - 1;
            if (idx < 0) {
                idx = 0;
            } else if (idx > 11) {
                idx = 11;
            }
            {
                int pick = func_020644cc(data_ov004_022476f8[idx].count) + 1;
                out->message = pick + data_ov004_022476f8[idx].base;
            }
        }
        kind = 0;
    }
    out->text = data_ov004_02254338[kind];
    if (!func_02073d90(world) && *func_0209d358(0, 0x4a) == 0 && kind == 0) {
        switch (out->message) {
            case 2:
            case 5:
            case 8:
            case 9:
            case 12:
            case 15:
            case 17:
            case 18:
            case 19:
            case 21:
            case 23:
            case 24:
            case 27:
            case 28:
            case 30:
            case 40:
            case 43: {
                void *actor = func_02082644(4);
                if (actor) {
                    func_020160d8(self, actor);
                }
            } break;
            default:
                break;
        }
    }
}
