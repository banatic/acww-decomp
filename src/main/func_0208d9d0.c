/* func_0208d9d0 @ 0x0208d9d0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208d9d0 {
    char pad_00[0x28];
    void *unk_28;
    int unk_2C;
    char pad1[0x8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[0x16];
    int unk_50;
    char pad_54[0x1];
    unsigned char unk_55;
};

struct UnkStruct_0208d9d0_2 {
    char pad_00[0x30];
    struct UnkStruct_0208d9d0 *unk_30;
    char pad1[0x16];
    unsigned char unk_4A;
    char pad2[0x4];
    unsigned char unk_4F;
};

extern struct UnkStruct_0208d9d0 *func_020a9034(int, int, int);
extern void func_02051694(struct UnkStruct_0208d9d0 *);

extern unsigned char data_021c82e8[];

void func_0208d9d0(struct UnkStruct_0208d9d0_2 *p)
{
    int val;

    if (p->unk_30) {
        return;
    }

    if (p->unk_4F != 0) {
        val = 0x9a;
    } else {
        val = 0x86;
    }

    p->unk_30 = func_020a9034(val, 2, 2);
    if (!p->unk_30) {
        return;
    }

    p->unk_30->unk_2C = 4;
    p->unk_30->unk_50 = 2;
    p->unk_30->unk_55 = 1;
    p->unk_30->unk_39 = 0;
    p->unk_30->unk_38 = 0xa;
    p->unk_30->unk_28 = (void *) data_021c82e8;

    func_02051694(p->unk_30);

    p->unk_4A = 1;
}
