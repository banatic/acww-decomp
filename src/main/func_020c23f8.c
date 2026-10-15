/* func_020c23f8 @ 0x020c23f8, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016884(int *param1, int param2, int *param3);
extern int func_02019de8(int *param1);
extern int func_02019d0c(int *param1, int param2, int param3, int param4, int a, short b, short c, int d, int e,
                         unsigned short f, unsigned short g);
extern void func_0201b38c(int *param1, int param2);
extern void func_0201b388(int *param1, int param2);
extern unsigned short data_020c80f8;

struct UnkStruct_020c23f8 {
    char pad_00[0x2a0];
    int unk_2A0;
    char pad_2A4[0x90];
    int unk_334;
    char pad_338[0x1b0];
    int unk_4E8;
    char pad_4EC[0x78];
    int unk_564;
};

int func_020c23f8(struct UnkStruct_020c23f8 *p)
{
    p->unk_4E8 |= 2;
    if (func_02016884(&p->unk_334, 0xab, &p->unk_2A0) && func_02019de8(&p->unk_564)) {
        func_02019d0c(&p->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        func_0201b38c(&p->unk_2A0, 0xac);
        func_0201b388(&p->unk_2A0, 0xac);
    }
    return 1;
}
