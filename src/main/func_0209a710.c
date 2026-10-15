/* func_0209a710 @ 0x0209a710, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209a710 {
    unsigned char pad_00[12];
    int unk_0C;
    unsigned char pad_10[0xa2];
    unsigned char unk_B2[4];
    unsigned char unk_B6[4];
    unsigned char unk_BA;
};

extern void func_0209a77c(struct UnkStruct_0209a710 *);
extern void func_02003728(int *, void *);
extern void func_0209bd30(struct UnkStruct_0209a710 *, int, unsigned short *, int);
#pragma arm
extern void MI_CpuCopy8(void *, const void *, unsigned int);
extern int func_020644cc(int);
#pragma thumb

void func_0209a710(struct UnkStruct_0209a710 *a, void *b, void *c)
{
    unsigned short local;

    func_0209a77c(a);
    func_02003728(&a->unk_0C, b);

    local = 0x155e;
    func_0209bd30(a, 9, &local, 0);

    MI_CpuCopy8(c, a->unk_B2, 4);
    MI_CpuCopy8(c, a->unk_B6, 4);

    a->unk_B6[3] = 1;
    a->unk_BA = func_020644cc(2) + 1;
}
