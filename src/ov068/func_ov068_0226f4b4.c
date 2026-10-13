/* func_ov068_0226f4b4 @ 0x0226f4b4, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
} ArrayElem;

extern ArrayElem *func_020b03f8(int);
extern void func_ov068_0226fcbc(void *self);

int func_ov068_0226f4b4(void *self)
{
    volatile unsigned short *flag = (volatile unsigned short *) ((char *) self + 0x378);
    int idx;
    ArrayElem *arr;

    *flag |= 0x10;
    *flag &= ~0x20;

    idx = *(unsigned int *) ((char *) self + 8) & 1;
    arr = func_020b03f8(1);
    idx &= 1;

    arr[idx].unk_00 = 0;
    arr[idx].unk_04 = 0;
    arr[idx].unk_08 = 0;
    arr[idx].unk_0C = 0x800;

    func_ov068_0226fcbc(self);
    return 1;
}
