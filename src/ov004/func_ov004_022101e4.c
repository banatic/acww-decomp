/* func_ov004_022101e4 @ 0x022101e4, 0x238 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 tag;
    u16 count;
} Resource;
extern void *func_ov004_0220e220(void *);
extern Resource *func_ov004_0220d9ec(void *, int);
extern Resource *func_ov004_0220d9f8(void *, int);
extern Resource *func_ov004_0220d9e0(void *, int);
extern Resource *func_ov004_0220d9d4(void *, int);
extern Resource *func_ov004_0220da04(void *, int);
extern void *func_02055e00(void *);
extern void *func_ov004_0220e050(void *);
extern void func_02056440(void *, void *, Resource *, u8, int, int);
extern void func_020563ec(void *, void *, Resource *, void *, u8, int, int);
extern void func_02055060(void *, Resource *, u8, int, int, u16);
typedef struct {
    u32 low : 12;
    u32 frame : 16;
    u32 high : 4;
} FrameBits;
#define FRAME(o) (((FrameBits *) (self + (o)))->frame)
void func_ov004_022101e4(char *self, int selector, u8 mode, int speed, u16 frame)
{
    int slot = selector & 1;
    if (func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), slot)) {
        Resource *res = func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), slot);
        int start;
        if (frame == 0xffff) {
            start = FRAME(0x82c);
        } else {
            start = (u16) (frame >= res->count ? res->count - 1 : frame);
        }
        func_02056440(self + 0x824, func_02055e00(self + 0x538), res, mode, speed, start);
    }
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), slot)) {
        Resource *res = func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), slot);
        int start;
        if (frame == 0xffff) {
            start = FRAME(0x7cc);
        } else {
            start = (u16) (frame >= res->count ? res->count - 1 : frame);
        }
        func_02056440(self + 0x7c4, func_02055e00(self + 0x538), res, mode, speed, start);
    }
    if (func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), slot)) {
        Resource *res = func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), slot);
        int start;
        if (frame == 0xffff) {
            start = FRAME(0x7ec);
        } else {
            start = (u16) (frame >= res->count ? res->count - 1 : frame);
        }
        func_02056440(self + 0x7e4, func_02055e00(self + 0x538), res, mode, speed, start);
    }
    if (func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), slot)) {
        Resource *res = func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), slot);
        int start;
        void *model;
        if (frame == 0xffff) {
            start = FRAME(0x80c);
        } else {
            start = (u16) (frame >= res->count ? res->count - 1 : frame);
        }
        model = func_02055e00(self + 0x538);
        func_020563ec(self + 0x804, model, res, func_ov004_0220e050(self + 0x6cc), mode, speed, start);
    }
    if (func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), slot)) {
        Resource *res = func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), slot);
        int start;
        if (frame == 0xffff) {
            start = FRAME(0x5dc);
        } else {
            start = (u16) (frame >= res->count ? res->count - 1 : frame);
        }
        func_02055060(self + 0x538, res, mode, speed, start, 0);
    }
}
