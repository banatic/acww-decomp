/* func_0208d0bc @ 0x0208d0bc, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df04(void *);
extern void func_0209e200(void *, short);
extern void func_020b8d74(int);
extern const short data_020d0a58[];

struct UnkStruct_0208d0bc {
    unsigned char pad_00[0xa4];
    unsigned char unk_A4;
    unsigned char unk_A5;
    unsigned char unk_A6;
    unsigned char unk_A7;
    unsigned char pad_A8[4];
    unsigned int unk_AC;
    unsigned int unk_B0;
    unsigned int unk_B4;
    unsigned char unk_B8[0x10];
    unsigned int unk_C8;
};

void func_0208d0bc(struct UnkStruct_0208d0bc *p, int a1, int a2)
{
    p->unk_B4 = a1;
    p->unk_C8 = 0;
    if (a1 != 0) {
        func_0209df04(p->unk_B8);
        func_0209e200(p->unk_B8, data_020d0a58[a1]);
        p->unk_AC = 0;
        p->unk_B0 = 0;
        p->unk_A4 = 1;
        p->unk_A5 = 1;
        p->unk_A6 = 1;
        p->unk_A7 = 1;
    }
    if (a2 == 0) {
        int v = (a1 == 0) ? 2 : 1;
        func_020b8d74(v);
    }
}
