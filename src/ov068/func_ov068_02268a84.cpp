/* func_ov068_02268a84 @ 0x02268a84, 0x130 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02268a84 {
    volatile unsigned short a;
    unsigned short b;
};
struct UnkStruct_02268a84_2 {
    char pad_00[0x1c];
    unsigned char unk_1C;
};
struct UnkStruct_02268a84_3 {
    char pad_00[0x514];
    char unk_514[0x564 - 0x514];
    char unk_564[0x83c - 0x564];
    char unk_83C[0x898 - 0x83c];
    char unk_898[0x9b4 - 0x898];
    char unk_9B4[0x9f0 - 0x9b4];
    unsigned char unk_9F0;
};

extern "C" void func_0202e118(struct UnkStruct_02268a84 *);
extern "C" void func_ov068_0226cfd4(struct UnkStruct_02268a84_3 *);
extern "C" void func_ov068_02266c34(void *, struct UnkStruct_02268a84_3 *, int, int, int, void *, int, int, int);
extern "C" void func_02019c20(void *, int, int, int, unsigned short, int);
extern "C" void func_02012508(void *, struct UnkStruct_02268a84_3 *, struct UnkStruct_02268a84 *, int, unsigned short);
extern "C" void func_020124e4(void *, int, int, int);
extern "C" void func_020121e0(void *, int);
extern "C" void func_0200442c(void *, int, int, int);
extern "C" void func_0202e194(struct UnkStruct_02268a84_3 *);
extern "C" void func_0201cbbc(void *);
extern int data_021fbee8;
extern int data_020c814c;
extern unsigned short data_020c80f8;

extern "C" int func_ov068_02268a84(struct UnkStruct_02268a84_2 *a0, struct UnkStruct_02268a84_3 *o)
{
    struct UnkStruct_02268a84 s;
    func_0202e118(&s);
    func_ov068_0226cfd4(o);
    func_ov068_02266c34(o->unk_898, o, 0, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
    int ok = 0;
    unsigned short lo = s.a;
    unsigned short hi = s.a;
    if (hi >= 0x1380 && lo <= 0x139f) {
        ok = 1;
    }
    if (ok) {
        unsigned short v = data_020c80f8;
        func_02019c20(o->unk_564, 1, 0xcd, 1, v, 0);
        func_02012508(o->unk_9B4, o, &s, 0xcd, v);
        func_020124e4(o->unk_9B4, 0x26, v, 1);
        func_020121e0(o->unk_9B4, 0x1000);
        o->unk_9F0 = 0;
        a0->unk_1C = 1;
    } else {
        unsigned short v = data_020c80f8;
        func_02019c20(o->unk_564, 1, 0xd6, 3, v, 0);
        func_02012508(o->unk_9B4, o, &s, 0xd6, v);
        func_020121e0(o->unk_9B4, 0);
        o->unk_9F0 = 1;
        a0->unk_1C = 0;
    }
    func_0202e194(o);
    func_0200442c(o->unk_514, 0x4f, 0x7f, 0);
    func_0201cbbc(o->unk_83C);
    return 1;
}