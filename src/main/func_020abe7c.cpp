/* func_020abe7c @ 0x020abe7c, 0x1c4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020abe7c {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

struct UnkStruct_020abe7c_2;
typedef void (UnkStruct_020abe7c_2::*PMF)(void);

struct UnkStruct_020abe7c_2 {
    unsigned char pad_00[0x20];
    UnkStruct_020abe7c sub20;
    unsigned char pad_24[0x48];
    UnkStruct_020abe7c sub6c;
    unsigned char pad_70[0x74];
    UnkStruct_020abe7c sube4;
    unsigned char pad_E8[0x54];
    int unk_13C;
    unsigned char unk_140;
    unsigned char pad_141;
    unsigned char unk_142;
    unsigned char pad_143;
    unsigned char unk_144;
};

extern PMF data_020e3f84, data_020e3ee4, data_020e3f8c, data_020e3eec, data_020e3f14, data_020e3f1c, data_020e3f7c,
    data_020e3f04, data_020e3f44, data_020e3f4c, data_020e3f0c, data_020e3f64;

extern "C" void func_020abbf8(UnkStruct_020abe7c_2 *);
extern "C" void func_020abaa8(UnkStruct_020abe7c_2 *);
extern "C" void func_020abc40(UnkStruct_020abe7c_2 *);
extern "C" int func_020abce4(UnkStruct_020abe7c_2 *);
extern "C" void func_020aca60(UnkStruct_020abe7c *, int *, int *);
extern "C" int func_020aca80(UnkStruct_020abe7c *);
extern "C" void func_0208e594(UnkStruct_020abe7c *, int, int);
extern "C" int func_020abccc(UnkStruct_020abe7c_2 *);
extern "C" void func_0208f184(UnkStruct_020abe7c *, int *, int *);
extern "C" void func_0208f210(UnkStruct_020abe7c *, int, int);

extern int data_021f45b0;
extern PMF data_021f4610[12];

extern "C" void func_020abe7c(UnkStruct_020abe7c_2 *p)
{
    int a, b, c, d;
    int r;

    if (p->unk_140) {
        p->unk_140 = 0;
        func_020abbf8(p);
    }
    if (p->unk_142) {
        p->unk_142 = 0;
        func_020abaa8(p);
    }
    if (p->unk_144) {
        p->unk_144 = 0;
        func_020abc40(p);
    }
    if (!(data_021f45b0 & 1)) {
        data_021f4610[0] = data_020e3f84;
        data_021f4610[1] = data_020e3ee4;
        data_021f4610[2] = data_020e3f8c;
        data_021f4610[3] = data_020e3eec;
        data_021f4610[4] = data_020e3f14;
        data_021f4610[5] = data_020e3f1c;
        data_021f4610[6] = data_020e3f7c;
        data_021f4610[7] = data_020e3f04;
        data_021f4610[8] = data_020e3f44;
        data_021f4610[9] = data_020e3f4c;
        data_021f4610[10] = data_020e3f0c;
        data_021f4610[11] = data_020e3f64;
        data_021f45b0 |= 1;
    }
    (p->*data_021f4610[p->unk_13C])();
    if (func_020abce4(p)) {
        func_020aca60(&p->sube4, &a, &b);
        r = func_020aca80(&p->sube4);
        func_0208e594(&p->sub20, a + 0x10, b + 7 + r);
    } else if (func_020abccc(p)) {
        func_0208f184(&p->sub6c, &c, &d);
        func_0208e594(&p->sub20, c + 0x46, d + 0x4c);
    }
    func_0208f210(&p->sub6c, 0x3c, 0x44);
    p->sub20.v3();
    p->sub6c.v3();
    p->sube4.v3();
}
