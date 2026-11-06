/* body_anim_heaps: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205f820 @ 0x0205f820, 0x28 bytes, Thumb
 * func_0205f808 @ 0x0205f808, 0x18 bytes, Thumb
 * func_0205f800 @ 0x0205f800, 0x8 bytes, Thumb
 * func_0205f7fc @ 0x0205f7fc, 0x2 bytes, Thumb
 * func_0205f7f8 @ 0x0205f7f8, 0x2 bytes, Thumb
 * func_0205f7bc @ 0x0205f7bc, 0x3c bytes, Thumb
 * func_0205f784 @ 0x0205f784, 0x38 bytes, Thumb
 * func_0205f77c @ 0x0205f77c, 0x6 bytes, Thumb
 * func_0205f774 @ 0x0205f774, 0x6 bytes, Thumb
 * func_0205f770 @ 0x0205f770, 0x2 bytes, Thumb
 * func_0205f750 @ 0x0205f750, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned long a[64];
} UnkStruct_0205f77c;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205f774;

extern unsigned int func_0205c4a4(int);
extern int func_020e9abc(void *);
extern unsigned char data_021c9ad0[];
extern unsigned char data_021cacd0[];
extern void func_0205c488(void);
extern u8 *data_020ccf94;
extern u32 func_020ea0e0(u32, u32);
extern void func_020e9b9c(void *);

void func_0205f7bc(u32 *arr);
void func_0205f784(void **array);

void func_0205f820(int argument0)
{
    void *condition_value0;
    int *ptr;

    func_0205c4a4((int) argument0);
    func_0205f7bc((u32 *) ((unsigned int) data_021cacd0));
    ptr = (int *) data_021c9ad0;
    if ((condition_value0 = (void *) (*ptr)) != 0) {
        func_020e9abc(condition_value0);
    }
}

void func_0205f808(void)
{
    func_0205f784((void **) ((void *) data_021cacd0));
    func_0205c488();
}

int func_0205f800(void)
{
    return 1896;
}

void func_0205f7fc(void *self) {}

void func_0205f7f8(void *object) {}

void func_0205f7bc(u32 *arr)
{
    u32 a;
    u32 count;
    u32 i;

    a = (*(u32 *) data_021c9ad0);
    count = data_020ccf94[0x6c];

    for (i = 0; i < count; i++) {
        arr[i] = func_020ea0e0((u32) func_0205f800(), a);
    }
}

void func_0205f784(void **array)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (array[i] != 0) {
            func_020e9b9c(array[i]);
            array[i] = 0;
        }
    }
    if ((*(void **) data_021c9ad0) != 0) {
        func_020e9b9c((*(void **) data_021c9ad0));
    }
}

unsigned long func_0205f77c(UnkStruct_0205f77c *p, int i)
{
    return p->a[i];
}

void func_0205f774(UnkStruct_0205f774 *p)
{
    p->unk_00 = 4;
}

void func_0205f770(void *object) {}

void func_0205f750(char *dst, char val)
{
    func_020e9b9c((void *) ((int) func_0205f77c((UnkStruct_0205f77c *) ((unsigned int) data_021cacd0), val)));
    *dst = val;
}
