/* func_0209d5f0 @ 0x0209d5f0, 0x190 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec {
    int x, y, z;
} Vec;
typedef struct UnkStruct_0209d5f0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s16 unk_04;
    s16 unk_06;
} UnkStruct_0209d5f0;
typedef struct UnkStruct_0209d5f0_2 {
    char pad_00[0x5c];
    Vec pos;
    char pad_68[0x8e - 0x68];
    s16 unk_8E;
} UnkStruct_0209d5f0_2;

extern int data_021dc6e8;
extern int data_021dc70c;
extern void *data_020ccf94;

extern UnkStruct_0209d5f0_2 *func_020961a8(int);
extern void *func_020b5e10(void);
extern int func_020b6140(void *, void *, UnkStruct_0209d5f0 *, Vec *, int *, s16 *, u8 *, u8 *, int, int);
extern int func_020b6044(void *, void *, int *, s16 *);
extern int func_020b5fc8(void *, void *, Vec *, Vec *);
extern void func_0209d83c(int *, int);
extern void func_0209d838(int *, void *);
extern void func_0209d830(int *, int);
extern void func_0209d82c(int *, int);
extern void func_0209d81c(int *, Vec *);
extern void func_0209d818(int *, int);
extern void func_0209d808(int *, Vec *);
extern void func_0204f7e0(Vec *, Vec *);
extern int func_0209d7c8(int);
extern int func_02073d90(void *);
extern int func_02073918(void *, int);
extern unsigned int func_0209d8b0(int *, int, int);
extern void func_0209d8e4(int *, int, int);
extern void func_02073820(void *);
extern void func_020737f0(void *, u8 *, int);
extern void func_02073770(void *, int, int);

int func_0209d5f0(void *self)
{
    UnkStruct_0209d5f0 s;
    int v20;
    int v24;
    Vec m28;
    Vec m34;
    Vec p40;
    Vec p4c;
    UnkStruct_0209d5f0_2 *e;
    int ok;
    int h;
    void *p;
    Vec *q;

    e = func_020961a8(4);
    ok = func_020b6140(func_020b5e10(), self, &s, &m28, &v20, &s.unk_04, &s.unk_02, &s.unk_01, 0, 0);
    func_0209d83c(&data_021dc6e8, 0);
    if (ok == 0) {
        goto fail;
    }
    if (e == 0) {
        goto fail;
    }
    q = &e->pos;
    p40.x = e->pos.x;
    p40.y = q->y;
    p40.z = q->z;
    h = e->unk_8E;
    func_020b6044(func_020b5e10(), self, &v24, &s.unk_06);
    func_020b5fc8(func_020b5e10(), self, &m34, &p40);
    func_0209d838(&data_021dc6e8, self);
    func_0209d830(&data_021dc6e8, v24);
    func_0209d82c(&data_021dc6e8, s.unk_00);
    if (v24 != 0) {
        func_0209d81c(&data_021dc6e8, &m34);
        func_0209d818(&data_021dc6e8, s.unk_06);
    } else {
        func_0209d81c(&data_021dc6e8, &p40);
        func_0209d818(&data_021dc6e8, h);
    }
    p4c.x = p40.x;
    p4c.y = p40.y;
    p4c.z = p40.z;
    p4c.z = p40.z + 0x2000;
    func_0204f7e0(&p4c, &p4c);
    p4c.x = p40.x;
    func_0209d808(&data_021dc6e8, &p4c);
    if (func_0209d7c8(s.unk_00) != 0) {
        p = data_020ccf94;
        if (func_02073d90(p) != 0) {
            if (func_02073918(p, 0) == 0) {
                goto task;
            }
        }
        if (func_0209d8b0(&data_021dc70c, s.unk_00, 0) <= 1) {
            func_0209d8e4(&data_021dc70c, s.unk_00, 0);
            func_0209d83c(&data_021dc6e8, 2);
        } else {
            func_0209d83c(&data_021dc6e8, 1);
        }
        goto ok;
    task:
        s.unk_03 = s.unk_00;
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, &s.unk_03, 1);
        func_02073770(p, 0x33, 0);
        goto ok;
    }
    func_0209d83c(&data_021dc6e8, 2);
ok:
    return 1;
fail:
    return 0;
}
