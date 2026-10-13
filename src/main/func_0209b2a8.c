/* func_0209b2a8 @ 0x0209b2a8, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 unk_0C[0x10];
    u8 unk_1C[0x10];
} UnkStruct_0209b2a8;
typedef struct {
    u8 d[0x20];
} OA;
typedef struct {
    u8 d[0x60];
} OB;

extern u8 data_020d1a48[];
extern u8 data_020e3494[];

extern int func_02003704(u8 *);
extern void func_02094fd4(OA *);
extern void func_02094fbc(OA *);
extern void func_020a8228(OB *);
extern void func_020a8210(OB *);
extern void func_02003618(u8 *, OA *);
extern void func_0203d7c4(int, void *);
extern void func_020a8c1c(void *);
extern int func_0209c54c(int *, int);
extern void func_020b49d4(OB *, u8 *, int);
extern void func_0200366c(u8 *, u8 *, int, void *);
extern u8 func_020644cc(int);
extern void func_02066104(void *, u8 *, u8 *, u8 *, u8 *, u8 *, void *, u8 *, u8 *, int);

void func_0209b2a8(UnkStruct_0209b2a8 *a0, void *a1)
{
    u8 buf[8];
    int v;
    u8 str[0x20];
    OA a;
    OB b;
    int i;
    int h;

    if (func_02003704(a0->unk_0C) && func_02003704(a0->unk_1C)) {
        func_02094fd4(&a);
        func_020a8228(&b);
        v = 0;
        func_02003618(a0->unk_1C, &a);
        func_0203d7c4(0, &a);
        func_020a8c1c(&a);
        func_02003618(a0->unk_0C, &a);
        func_0203d7c4(1, &a);
        for (i = 0; i < 6; i++) {
            h = func_0209c54c(&v, i);
            func_020a8c1c(&b);
            buf[0] = (u8) v;
            func_020b49d4(&b, buf, h);
            func_0203d7c4(i + 2, &b);
        }
        func_0200366c(a0->unk_0C, str, 0x1e, data_020d1a48);
        buf[1] = func_020644cc(10);
        buf[2] = func_020644cc(10);
        buf[3] = func_020644cc(10);
        buf[4] = func_020644cc(10);
        func_02066104(a1, &buf[1], &buf[2], &buf[3], &buf[4], str, data_020e3494, a0->unk_0C, a0->unk_1C, 1);
        func_020a8210(&b);
        func_02094fbc(&a);
    }
}
