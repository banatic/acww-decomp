/* func_ov068_0226f348 @ 0x0226f348, 0x68 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b03f8(void);

struct UnkStruct_0226f348 {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x50];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x310];
    unsigned short unk_378;
    char pad_37A[2];
    int unk_37C;
    int unk_380;
    int unk_384;
};

struct UnkStruct_0226f348_2 {
    int a;
    int b;
    int c;
    int d;
};

int func_ov068_0226f348(struct UnkStruct_0226f348 *p)
{
    unsigned short *flags;
    int idx;
    struct UnkStruct_0226f348_2 *arr;

    flags = (unsigned short *) ((char *) p + 0x378);
    *flags &= ~0x10;
    *flags |= 0x20;

    idx = p->unk_08 & 1;
    arr = (struct UnkStruct_0226f348_2 *) func_020b03f8();
    idx = idx & 1;

    arr[idx].a = 0;
    arr[idx].b = 0;
    arr[idx].c = 0;
    arr[idx].d = 0x800;

    p->unk_37C = p->unk_5C;
    p->unk_380 = p->unk_60;
    p->unk_384 = p->unk_64;

    return 1;
}
