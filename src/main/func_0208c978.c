/* func_0208c978 @ 0x0208c978, 0x1b0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    int w1;
} UnkStruct_0208c978;

typedef struct UnkStruct_0208c978_2 {
    u8 pad_00[0xa4];
    u8 a4;
    u8 a5;
    u8 pad_A6[0xb4 - 0xa6];
    int b4;
    UnkStruct_0208c978 b8;
    UnkStruct_0208c978 c0;
    int c8;
    u8 pad_CC[0xdc - 0xcc];
    u32 dc;
    u32 e0;
} UnkStruct_0208c978_2;

extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void func_0209df04(UnkStruct_0208c978 *k);
extern int func_0209e3ac(UnkStruct_0208c978 *a, UnkStruct_0208c978 *b, int m);
extern void func_0209e040(UnkStruct_0208c978 *a, UnkStruct_0208c978 *b);
extern int func_020b65c4(void);
extern void func_0200467c(int a);
extern void func_020b8d74(int a);
extern u64 OS_GetTick(void);

void func_0208c978(UnkStruct_0208c978_2 *s)
{
    UnkStruct_0208c978 k0;
    UnkStruct_0208c978 k8;
    UnkStruct_0208c978 k10;
    int f;
    int g;
    int t;
    int t1;
    int t2;
    int h;
    int u;
    u8 *p5;
    u8 *p4;
    u8 b0;
    u8 b1;
    u64 tick;
    u64 prev;
    u64 tick2;

    if (s->c8 > 0) {
        s->c8 = s->c8 - 1;
    }
    if (s->b4 != 0) {
        MI_CpuCopy8(&s->b8, &k0, 8);
        k8.unk_00 = 0;
        k8.w1 = 0;
        func_0209df04(&k8);
        t = func_0209e3ac(&k8, &k0, 0x3f);
        f = (t == 0 || t == 1) ? 1 : 0;
        g = f;
        if (f != 0) {
            k0.unk_00 = 0;
            k0.w1 = 0;
        } else {
            MI_CpuCopy8(&k8, &k10, 8);
            func_0209e040(&k0, &k10);
            h = f;
            t1 = (func_0209e3ac(&s->c0, &k0, 1) != 0) ? 1 : 0;
            u = h | t1;
            f = (u != 0) ? 1 : 0;
            t2 = (func_0209e3ac(&s->c0, &k0, 2) != 0) ? 1 : 0;
            h = h | t2;
            g = (h != 0) ? 1 : 0;
        }
        p5 = &s->a5;
        *p5 = (u8) (((s->a5 | f) != 0) ? 1 : 0);
        p4 = &s->a4;
        *p4 = (u8) (((s->a4 | g) != 0) ? 1 : 0);
        if (f != 0 || g != 0) {
            MI_CpuCopy8(&k0, &s->c0, 8);
            b0 = ((u8 *) &k0)[0];
            b1 = ((u8 *) &k0)[1];
            if (b1 == 0) {
                if (b0 == 0) {
                    s->c8 = 0x258;
                    s->b4 = 0;
                    if (func_020b65c4() != 0x2e) {
                        func_0200467c(0x65);
                    }
                    func_020b8d74(3);
                } else if (b0 <= 0xa) {
                    tick = OS_GetTick();
                    if (((tick - *(u64 *) &s->dc) << 6) / 0x82eaULL <= 0x44cULL) {
                        if (func_020b65c4() != 0x2e) {
                            func_0200467c(0x64);
                        }
                    }
                    s->dc = (u32) tick;
                    s->e0 = (u32) (tick >> 32);
                } else if (b0 >= 0xb) {
                    tick2 = OS_GetTick();
                    s->dc = (u32) tick2;
                    s->e0 = (u32) (tick2 >> 32);
                }
            }
        }
    }
}
