/* func_0203df10 @ 0x0203df10, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961a8(int);
extern int func_0203ec98(void);
extern void func_0206f5cc(void);
extern int func_02095f28(void);
extern void func_02095f08(int);
extern struct UnkStruct_0203df10 *func_0203f504(void);

struct UnkStruct_0203df10 {
    char pad_00[0xc];
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
};

extern struct UnkStruct_0203df10 *data_021c72b8;

int func_0203df10(void)
{
    struct UnkStruct_0203df10 *p;
    if (func_020961a8(4) == 0) {
        return 0;
    }
    if (func_0203ec98() != 0) {
        func_0206f5cc();
        return 0;
    }
    if (func_02095f28() == 0) {
        return 0;
    }

    func_02095f08(1);
    p = func_0203f504();
    p->unk_0C = 0;
    p->unk_10 = 0;
    p->unk_15 = 0xd;
    p->unk_14 = 3;
    p->unk_16 = 5;
    data_021c72b8 = p;
    return 1;
}
