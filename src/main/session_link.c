/* session_link: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02074120 @ 0x02074120, 0x30 bytes, Thumb
 * func_020740dc @ 0x020740dc, 0x44 bytes, Thumb
 * func_020740b4 @ 0x020740b4, 0x28 bytes, Thumb
 * func_020740a0 @ 0x020740a0, 0x12 bytes, Thumb
 * func_02074078 @ 0x02074078, 0x28 bytes, Thumb
 * func_02073fdc @ 0x02073fdc, 0x9c bytes, Thumb
 * func_02073fcc @ 0x02073fcc, 0x10 bytes, Thumb
 * func_02073fc8 @ 0x02073fc8, 0x2 bytes, Thumb
 * func_02073fb4 @ 0x02073fb4, 0x14 bytes, Thumb
 * func_02073f90 @ 0x02073f90, 0x22 bytes, Thumb
 * func_02073f00 @ 0x02073f00, 0x8e bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} Unk028CCF94;

struct GameState {
    char pad_00[0x64];
    int flag;
};

typedef struct {
    unsigned char pad_00[0x68];
    unsigned int unk_68;
} UnkStruct_02073f90;

extern Unk028CCF94 *data_020ccf94;
extern int func_02073dd4(Unk028CCF94 *p, int v);
extern void func_020a6f74(int a, int b);
extern int func_02073918(int, int);
extern void func_0207428c(void);
extern int func_020749c4(void);
extern int func_020732c0(void *param1);
extern void func_020732cc(void *param1, int param2);
extern u16 func_0207315c(u16 *);
extern int func_02073de4(u16 *);
extern void func_02073180(u16 *, u16);
extern void func_02073168(u16 *, u16);
extern u16 func_02073174(u16 *);
extern unsigned int func_02073044(void);
extern int func_020ec260(void);
extern int func_020ec920(void);
extern u16 func_020ec1f8(void);
extern void func_020738e8(UnkStruct_02073f90 *ptr);
extern void func_020732e4(UnkStruct_02073f90 *ptr, int value);
extern void func_02073db4(void *);
extern void func_02073d74(void *, int);
extern void func_02073d6c(void *, int);
extern void func_02073ca8(void *);
extern void func_02073c48(void *);
extern void func_02073b84(void *);
extern void func_0207388c(void *);
extern void func_0207385c(void *);
extern void func_02073754(void *);
extern void func_020736a0(void *);
extern void func_0207357c(void *);
extern void func_020734b4(void *);
extern void func_02073410(void *);
extern void func_020733ac(void *);
extern void func_02073354(void *);
extern void func_02073344(void *);
extern void func_0207318c(void *);
extern void func_020732b4(void *, int);

void func_02073fb4(int arg);
void func_02073f90(UnkStruct_02073f90 *ptr);
void func_02073f00(void *r0);

void func_02074120(void)
{
    int value = data_020ccf94->unk_64;
    if (func_02073dd4(data_020ccf94, value) == 0) {
        func_020a6f74(3, 7);
    } else {
        func_020a6f74(value, 7);
    }
}

int func_020740dc(void)
{
    int r5 = 0;
    int r4 = 3;
    int r6 = (*(int *) &data_020ccf94);
    int r7 = 1;
    do {
        if (func_02073dd4((Unk028CCF94 *) r6, r4) != 0) {
            if (func_02073918(r6, r4) == 0) {
                r5 |= (unsigned char) (r7 << r4);
            }
        }
        r4--;
    } while (r4 >= 0);
    return r5;
}

unsigned int func_020740b4(void)
{
    unsigned int result;
    int field;

    result = (unsigned int) func_020740dc();
    field = (*(struct GameState * *) &data_020ccf94)->flag;
    if (field < 4) {
        result |= (unsigned short) (1 << field);
    }
    return result;
}

void func_020740a0(void)
{
    func_0207428c();
    func_020749c4();
}

void func_02074078(void)
{
    unsigned int *r4;
    int r0;
    int r1;

    r4 = (unsigned int *) (*(unsigned int *) &data_020ccf94);
    r0 = func_020732c0(r4);
    r1 = r0;
    if ((r0 & 0x40) == 0) {
        r1 = r0 | 0x40;
        func_020732cc(r4, r1);
    }
}

int func_02073fdc(int a)
{
    u16 *p = (*(u16 * *) &data_020ccf94);
    u16 n = func_0207315c(p);
    u16 v;

    if (n != 0) {
        if (func_02073de4(p) != 0) {
            p = (*(u16 * *) &data_020ccf94);
            func_02073180(p, 0);
            func_02073168(p, 0);
        } else {
            u16 c = func_02073174(p);
            if (c >= n) {
                return 1;
            }
            func_02073180(p, (u16) (c + 1));
        }
    }

    if (a < 0) {
        goto neg;
    }
    v = (u16) a;
    if (func_020ec260() == 0) {
        goto chk;
    }
    if (a <= 0) {
        goto ret0;
    }
    func_02073044();
    if (func_020ec920() != 0) {
        goto ret0;
    }
    return 1;
chk:
    if ((v & func_020ec1f8()) == v) {
        goto ret0;
    }
    return 1;
neg:
    if (func_020ec1f8() != 0) {
        goto ret0;
    }
    return 1;
ret0:
    return 0;
}

void *func_02073fcc(void *ptr)
{
    func_02073fb4((int) ptr);
    return ptr;
}

void func_02073fc8(void *object) {}

void func_02073fb4(int arg)
{
    func_02073f90((UnkStruct_02073f90 *) arg);
    func_02073f00((void *) arg);
}

void func_02073f90(UnkStruct_02073f90 *ptr)
{
    ptr->unk_68 = 4;
    func_020738e8(ptr);
    func_020732e4(ptr, 0);
    func_020732cc((void *) ptr, 0);
}

void func_02073f00(void *r0)
{
    func_02073db4(r0);
    func_02073d74(r0, 0);
    func_02073d6c(r0, 3);
    func_02073ca8(r0);
    func_02073c48(r0);
    func_02073b84(r0);
    *(int *) ((char *) r0 + 0x64) = 4;
    func_0207388c(r0);
    func_0207385c(r0);
    func_02073754(r0);
    func_020736a0(r0);
    func_0207357c(r0);
    func_020734b4(r0);
    func_02073410(r0);
    func_020733ac(r0);
    func_02073354(r0);
    func_02073344(r0);
    func_0207318c(r0);
    func_02073180((u16 *) r0, 0);
    func_02073168((u16 *) r0, 0);
    func_020732b4(r0, 0);
}
