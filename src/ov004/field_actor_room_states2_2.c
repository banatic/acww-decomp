/* field_actor_room_states2_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229ea8 @ 0x02229ea8, 0x4 bytes, Thumb
 * func_ov004_02229e74 @ 0x02229e74, 0x34 bytes, Thumb
 * func_ov004_02229e70 @ 0x02229e70, 0x2 bytes, Thumb
 * func_ov004_02229d7c @ 0x02229d7c, 0xf4 bytes, Thumb
 * func_ov004_02229d5c @ 0x02229d5c, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char unk_00;
} UnkStruct_02229ea8;

extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern int func_0200dc8c(void *);
extern int func_02008258(void *, int);
extern int func_0200dc10(void *);
extern int func_ov004_0222a23c(void *, int, int, int, int);
extern int func_02056f94(void *);
extern int func_0200d4e8(void *, int, int, int);
extern void func_02056fcc(void *, int, int, int, unsigned);
extern void func_02010f5c(int);
extern void func_02010d64(int);
extern int func_02010ca4(int);

void func_ov004_02229ea8(UnkStruct_02229ea8 *p, unsigned char v)
{
    p->unk_00 = v;
}

void func_ov004_02229e74(unsigned char *self, unsigned char *p, int previous)
{
    unsigned char *w;
    w = self + 0x7d4;
    if (*(unsigned char *) (p + 0xc) != 0) {
        func_020109a0(self, 0x1b, 3, 0);
    } else {
        func_020109a0(self, 0x1c, 3, 0);
    }
    func_ov004_02229ea8((UnkStruct_02229ea8 *) w, 0);
}

void func_ov004_02229e70(void *callbackObject, int event) {}

void func_ov004_02229d7c(char *self)
{
    if (*(u8 *) (self + 0x2e4) == 3) {
        char *q = self + 0x7d4;
        int k;
        if (*(u8 *) q == 0 && func_0200dc8c(self) < 0x19a) {
            func_ov004_02229ea8((UnkStruct_02229ea8 *) q, 1);
        }
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        k = func_0200dc10(self);
        if (*(u8 *) q != 0 && func_0200dc8c(self) > 0x19a && (k == 3 || k == 1)) {
            func_ov004_0222a23c(self, 1, 1, 5, -1);
        } else if (func_02056f94(self + 0x2d0) != 0) {
            if (*(u8 *) (self + 0x141) != 0) {
                func_ov004_0222a23c(self, 0, 1, 5, -1);
            } else {
                func_0200d4e8(self, 3, 1, -1);
            }
        }
    } else if (func_02056f94(self + 0x2d0) != 0) {
        func_02056fcc(self + 0x2d0, 0, 3, 0x1000, ((unsigned) *(int *) (self + 0x2d4) << 4) >> 16);
    }
}

void func_ov004_02229d5c(int arg)
{
    func_02010f5c(arg);
    func_02010d64(arg);
    func_02010ca4(arg);
    func_ov004_02229d7c((char *) arg);
}
