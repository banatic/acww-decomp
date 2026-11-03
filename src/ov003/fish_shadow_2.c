/* fish_shadow_2: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222902c @ 0x0222902c, 0xd4 bytes, Thumb
 * func_ov003_02228fe8 @ 0x02228fe8, 0x44 bytes, Thumb
 * func_ov003_02228fd0 @ 0x02228fd0, 0x18 bytes, Thumb
 * func_ov003_02228f8c @ 0x02228f8c, 0x44 bytes, Thumb
 * func_ov003_02228f54 @ 0x02228f54, 0x38 bytes, Thumb
 * func_ov003_02228f48 @ 0x02228f48, 0xc bytes, Thumb
 * func_ov003_02228f44 @ 0x02228f44, 0x2 bytes, Thumb
 */

#include "types.h"

extern char data_0213efe8[];
extern char data_0213f020[];
extern void func_020f5958(char *self);
extern void *func_02032c64(char *p);
extern void func_0209d34c(char *p);
extern void *func_0205577c(char *p);
extern void *func_02055210(char *p);
void *func_020551e0(void *p);
void *func_02055764(void *p);
void func_0209d340(void *p);
void *func_02032c50(void *p);
void func_020f5948(void *p);
extern int data_ov003_0223c0d4;
void *func_02056578(void *p);
void *func_0209d11c(void *p);
void func_020565ec(void *p);
void func_0209d0a4(void *p);
int func_0209d104(void *p);

void func_ov003_02228f48(u8 *p);
void func_ov003_02228f44(void *object);

char *func_ov003_0222902c(char *self)
{
    func_020f5958(self);
    *(void **) (self + 0x40) = data_0213efe8;
    *(void **) (self + 0x40) = data_0213f020;
    func_02032c64(self + 0x4c);
    func_0209d34c(self + 0x7c);
    func_0205577c(self + 0x84);
    func_02055210(self + 0x144);
    *(int *) (self + 0x208) = 0;
    *(int *) (self + 0x20c) = 0;
    func_ov003_02228f48((u8 *) (self + 0x248));
    *(s8 *) (self + 0x7e) = -1;
    *(int *) (self + 0x244) = -1;
    *(int *) (self + 0x80) = 0;
    *(u8 *) (self + 0x1fc) = 2;
    *(u8 *) (self + 0x201) = 0;
    *(int *) (self + 0x204) = -1;
    *(s8 *) (self + 0x227) = -1;
    *(int *) (self + 0x22c) = 0;
    *(u8 *) (self + 0x224) = 0;
    *(u8 *) (self + 0x23c) = 0;
    *(int *) (self + 0x120) = 0x1000;
    *(int *) (self + 0x124) = 0x1000;
    *(int *) (self + 0x128) = 0x1000;
    return self;
}

void *func_ov003_02228fe8(char *self)
{
    func_ov003_02228f44(self + 0x248);
    func_020551e0(self + 0x144);
    func_02055764(self + 0x84);
    func_0209d340(self + 0x7c);
    func_02032c50(self + 0x4c);
    func_020f5948(self);
    return self;
}

void *func_ov003_02228fd0(void *self)
{
    *(int *) self = (int) &data_ov003_0223c0d4;
    func_02056578(self);
    return self;
}

void *func_ov003_02228f8c(char *self)
{
    func_0209d34c((char *) (self + 4));
    func_0209d11c(self + 8);
    func_02055210((char *) (self + 0x58));
    func_020565ec(self + 0x11c);
    *(int *) (self + 0x11c) = (int) &data_ov003_0223c0d4;
    *(int *) self = 0;
    func_0209d0a4(self + 8);
    return self;
}

void *func_ov003_02228f54(char *self)
{
    *(int *) (self + 0x11c) = (int) &data_ov003_0223c0d4;
    func_02056578(self + 0x11c);
    func_020551e0(self + 0x58);
    func_0209d104(self + 8);
    func_0209d340(self + 4);
    return self;
}

void func_ov003_02228f48(u8 *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

void func_ov003_02228f44(void *object) {}
