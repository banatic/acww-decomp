/* func_ov068_0226f5cc @ 0x0226f5cc, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Global;

extern Global data_021fbee8;

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
} Elem;

extern void *func_020b03f8(void);

int func_ov068_0226f5cc(unsigned char *self)
{
    int idx;
    Elem *arr;

    *(unsigned short *) (self + 0x378) |= 0x10;
    *(unsigned short *) (self + 0x378) &= ~0x20;
    *(unsigned short *) (self + 0x396) = 0;

    idx = *(unsigned int *) (self + 8) & 1;
    arr = (Elem *) func_020b03f8();
    idx &= 1;

    arr[idx].a = 0;
    arr[idx].b = 0;
    arr[idx].c = 0;
    arr[idx].d = 0x800;

    *(unsigned int *) (self + 0x308) = data_021fbee8.a;
    *(unsigned int *) (self + 0x30c) = data_021fbee8.b;
    *(unsigned int *) (self + 0x310) = data_021fbee8.c;

    *(unsigned int *) (self + 0xa8) = 0;

    return 1;
}
