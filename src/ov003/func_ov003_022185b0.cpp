/* func_ov003_022185b0 @ 0x022185b0, 0xb4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022185b0 {
    int unk_00, unk_04;
    short unk_08;
    unsigned char unk_0A, unk_0B;
};
struct UnkStruct_022185b0_2 {
    char pad_00[0xc];
    struct UnkStruct_022185b0 p;
};
struct UnkStruct_022185b0_3 {
    char pad_00[0x5c];
    char unk_5C[0x7d4 - 0x5c];
    char unk_7D4[0x800 - 0x7d4];
    int unk_800;
    char pad_804[0x8f0 - 0x804];
    char unk_8F0[4];
};

extern "C" unsigned int *func_0200f27c(struct UnkStruct_022185b0_3 *, int);
extern "C" void func_020109a0(struct UnkStruct_022185b0_3 *, int b, int c, unsigned short d);
extern "C" void func_020109fc(struct UnkStruct_022185b0_3 *, int, int, int);
extern "C" void func_ov003_022186b0(void *, int, int, int, int, int);
extern "C" void func_ov003_02218688(void *, int, int, int, int);
extern "C" int func_02073908(int, int);
extern "C" int func_ov003_02220384(void *, int);
extern int data_020ccf94;

extern "C" void func_ov003_022185b0(struct UnkStruct_022185b0_3 *o, struct UnkStruct_022185b0_2 *qq, int previous)
{
    func_0200f27c(o, 4);
    struct UnkStruct_022185b0 *p = &qq->p;
    void *dst = o->unk_7D4;
    int extra = 0;
    switch (p->unk_0A) {
        case 0:
            func_020109a0(o, 0x33, 3, 0);
            break;
        case 1:
            func_020109a0(o, 0x32, 3, 0);
            break;
        case 2:
            extra = 0xc;
            func_020109fc(o, 0, 3, 0);
            break;
    }
    int t = p->unk_0A;
    int x = p->unk_00;
    int y = p->unk_04;
    int z = p->unk_08;
    func_ov003_022186b0(dst, t, x, y, z, extra);
    func_ov003_02218688(o->unk_8F0, t, x, y, z);
    int b = (func_02073908(data_020ccf94, o->unk_800) != 0);
    func_ov003_02220384(o->unk_5C, b);
}