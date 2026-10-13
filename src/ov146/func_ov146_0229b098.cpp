/* func_ov146_0229b098 @ 0x0229b098, 0x290 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b098_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

struct UnkStruct_0229b098 {
    char pad_00[0x94];
    void *unk_94;
    char pad_98[0xc];
    int unk_A4;
    char pad_A8[6];
    short unk_AE;
    unsigned char unk_B0;
    unsigned char unk_B1;
    char pad_B2[5];
    volatile unsigned char unk_B7;
    unsigned char unk_B8;
    char pad_B9[2];
    unsigned char unk_BB;
    char pad_BC[0xe];
    unsigned char arr_ca[0x20];
    unsigned char arr_ea[0x20];
    char pad_10A[0x14c2];
    char unk_15CC;
    char pad_15CD[0x91b];
    UnkStruct_0229b098_2 sub1ee8;
    char pad_1EEC[0xc8];
    UnkStruct_0229b098_2 sub1fb4;
};

extern "C" {
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern int func_ov146_02299670(UnkStruct_0229b098 *, int);
extern void func_0208aa60(void *, int, void *);
extern void func_02088df8(int, const void *, int, void *, int, int, int, int, int, int, int, int);
extern const char data_ov146_0229b5e0[];
extern const char data_ov146_0229b5b0[];
extern const char data_ov146_0229b618[];
extern const char data_ov146_0229b550[];
extern const char data_ov146_0229b590[];
extern const char data_ov146_0229b498[];
extern const char data_ov146_0229b418[];
extern const char data_ov146_0229b420[];
extern const char data_ov146_0229b460[];
extern const char data_ov146_0229b490[];
extern const char data_ov146_0229b4d0[];
extern const char data_ov146_0229b4f0[];
extern const char data_ov146_0229b510[];
extern const char data_ov146_0229b530[];
extern const char data_ov146_0229b570[];
}

extern "C" int func_ov146_0229b098(UnkStruct_0229b098 *s)
{
    char *d;
    char *e;
    int i;
    int idx;
    const char *f;

    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(&s->unk_15CC);
    }
    if (func_ov146_02299670(s, 1) == 0) {
        return 0;
    }
    s->sub1fb4.v2();
    func_0208aa60(&s->sub1ee8, 0, s->unk_94);
    s->sub1ee8.v2();
    d = (char *) s->unk_94 + 0x60;
    e = d - (s->unk_A4 & 0xf);
    for (i = 0; i < 7; i++) {
        int k = i + s->unk_AE;
        if (k < 0x20 && s->unk_BB < 0x20 && s->unk_BB == s->arr_ea[k]) {
            func_02088df8(1, data_ov146_0229b5e0, 0x80, e, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            func_02088df8(1, data_ov146_0229b5b0, 0x80, e, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        idx = i + s->unk_AE;
        if (idx < 0x20) {
            const char *tbl[5] = {0, data_ov146_0229b418, data_ov146_0229b460, data_ov146_0229b420, data_ov146_0229b490};
            f = tbl[s->arr_ca[idx]];
            if (f != 0) {
                func_02088df8(1, f, 0x80, e, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            }
        }
        e += 0x10;
    }
    func_02088df8(1, data_ov146_0229b618, 0x80, d, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, data_ov146_0229b550, 0x80, d, s->unk_B1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, data_ov146_0229b590, 0x80, d, s->unk_B0, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, data_ov146_0229b498, 0x80, d, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    {
        const char *tb2[5] = {data_ov146_0229b570, data_ov146_0229b4d0, data_ov146_0229b4f0, data_ov146_0229b510,
                              data_ov146_0229b530};
        if (s->unk_B7 != 0) {
            s->unk_B7 = s->unk_B7 - 1;
        } else {
            s->unk_B8 = s->unk_B8 + 1;
            if (s->unk_B8 >= 5) {
                s->unk_B8 = 0;
            }
            s->unk_B7 = 0xa;
        }
        func_02088df8(1, tb2[s->unk_B8], 0x80, d, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    return 1;
}
