/* func_ov068_0226f230 @ 0x0226f230, 0x68 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b03f8(void);

struct UnkStruct_0226f230 {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x2e8];
    int unk_2F4;
    char pad_2F8[0x80];
    unsigned short unk_378;
    char pad_37A[0x1c];
    unsigned short unk_396;
};

extern void func_ov068_0226fc48(struct UnkStruct_0226f230 *);

struct UnkStruct_0226f230_2 {
    int a;
    int b;
    int c;
    int d;
};

int func_ov068_0226f230(struct UnkStruct_0226f230 *p)
{
    unsigned short *flags;
    int idx;
    struct UnkStruct_0226f230_2 *arr;

    flags = (unsigned short *) ((char *) p + 0x378);
    *flags &= ~0x10;
    *flags |= 0x20;

    idx = p->unk_08 & 1;
    arr = (struct UnkStruct_0226f230_2 *) func_020b03f8();
    idx = idx & 1;

    arr[idx].a = 0;
    arr[idx].b = 0;
    arr[idx].c = 0;
    arr[idx].d = 0x800;

    p->unk_396 = 0;
    p->unk_2F4 = p->unk_2F4 >> 1;
    func_ov068_0226fc48(p);

    return 1;
}
