/* fish_shadow: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02228e8c @ 0x02228e8c, 0x38 bytes, Thumb
 * func_ov003_02228e58 @ 0x02228e58, 0x34 bytes, Thumb
 * func_ov003_02228e20 @ 0x02228e20, 0x38 bytes, Thumb
 * func_ov003_02228dfc @ 0x02228dfc, 0x24 bytes, Thumb
 * func_ov003_02228d48 @ 0x02228d48, 0xb4 bytes, Thumb
 * func_ov003_02228d1c @ 0x02228d1c, 0x2c bytes, Thumb
 * func_ov003_02228cd4 @ 0x02228cd4, 0x48 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x80];
    int unk_80;
    char pad_84[0x1c8];
} UnkStruct_02228dfc;

extern int data_020da13c;
extern int data_ov003_0223bfcc;
void *func_020ee660(void *p);
void func_0209d2b8(void *p);
void func_0209d2b4(void *p);
void func_020ee62c(void *p);
void func_020edf54(void *p);
extern UnkStruct_02228dfc data_ov003_0225f76c[];
extern char data_ov003_0225f4dc[];
extern void func_0209129c(int h);
extern void func_020604fc(int v, int z);
extern int data_ov003_0225f220;
extern int data_ov003_0225f224;
extern int data_ov003_0225f228;
void *func_0209d238(void *p, void *q);
void func_0209d0a4(void *p);
extern int data_ov003_0225f278;
extern int data_ov003_0225f320[];
void func_0205502c(void *p);
int func_02055454(void *p);
void func_0209d090(void *p);
void func_0209d200(void *p, void *q);

void *func_ov003_02228e8c(char *self)
{
    func_020ee660(self);
    *(int *) self = (int) &data_020da13c;
    *(int *) self = (int) &data_ov003_0223bfcc;
    func_0209d2b8(self + 0x50);
    func_0209d2b8(self + 0x68);
    *(int *) (self + 0x80) = 0;
    return self;
}

void *func_ov003_02228e58(char *self)
{
    *(int *) self = (int) &data_ov003_0223bfcc;
    func_0209d2b4(self + 0x68);
    func_0209d2b4(self + 0x50);
    *(int *) self = (int) &data_020da13c;
    func_020ee62c(self);
    return self;
}

void *func_ov003_02228e20(char *self)
{
    *(int *) self = (int) &data_ov003_0223bfcc;
    func_0209d2b4(self + 0x68);
    func_0209d2b4(self + 0x50);
    *(int *) self = (int) &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

int func_ov003_02228dfc(void *a, int i)
{
    int r = 0;
    UnkStruct_02228dfc *e;
    if (i >= 0 && i < 6) {
        e = &data_ov003_0225f76c[i];
        e->unk_80 = 2;
        r = 1;
    }
    return r;
}

void func_ov003_02228d48(void *unused, int i)
{
    if (i >= 0 && i < 6) {
        char *rec = ((char *) data_ov003_0225f76c) + i * 0x24c;
        int *sl;
        int v;
        *(int *) (rec + 0x80) = 0;
        func_0209129c(*(int *) (rec + 0x204));
        *(int *) (rec + 0x204) = -1;
        if (*(u8 *) (rec + 0x1fc) == 0) {
            *(u8 *) (rec + 0x1fc) = 3;
        } else if (*(u8 *) (rec + 0x1fc) == 1) {
            *(u8 *) (rec + 0x1fc) = 4;
        }
        sl = (int *) (rec + 0x208);
        sl[0] = i;
        sl[1] = 0;
        v = *(int *) (rec + 0x22c);
        if (v != 0) {
            if (*(int *) (data_ov003_0225f4dc + *(s8 *) (rec + 0x227) * 0xa4 + 0x40) != 1) {
                func_020604fc(v, 0);
                *(int *) (rec + 0x22c) = 0;
                *(s8 *) (rec + 0x227) = -1;
                *(u8 *) (rec + 0x23c) = 0;
            }
            *(u8 *) (rec + 0x224) = 0;
        }
    }
}

int func_ov003_02228d1c(char *self)
{
    data_ov003_0225f220 = 2;
    func_0209d238(self + 0x68, &data_ov003_0225f224);
    func_0209d0a4(&data_ov003_0225f228);
    return 1;
}

void func_ov003_02228cd4(char *self)
{
    data_ov003_0225f220 = 0;
    func_0205502c(&data_ov003_0225f278);
    func_02055454(&data_ov003_0225f278);
    func_0209d090(&data_ov003_0225f228);
    func_0209d200(self + 0x68, &data_ov003_0225f224);
    data_ov003_0225f320[13] = 0;
    data_ov003_0225f320[14] = 0;
}
