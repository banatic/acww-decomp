/* func_ov142_0229bf6c @ 0x0229bf6c, 0x260 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229bf6c_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct Cell {
    char b[8];
};

struct UnkStruct_0229bf6c {
    char pad_00[0x94];
    void *unk_94;
    void *unk_98;
    int unk_9C;
    char pad_A0[0x14];
    short unk_B4;
    char pad_B6[2];
    short unk_B8;
    char pad_BA[2];
    unsigned char unk_BC;
    unsigned char unk_BD;
    unsigned char unk_BE;
    unsigned char unk_BF;
    char pad_C0[0x28];
    char unk_E8;
    char pad_E9[0x63];
    UnkStruct_0229bf6c_2 sub14c;
    char pad_150[0x44];
    char unk_194;
};

extern "C" {
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern int func_ov142_02299668(UnkStruct_0229bf6c *, int);
extern void func_ov002_0220ad18(void *, void *);
extern short func_ov142_0229a6d8(UnkStruct_0229bf6c *);
extern int func_020896b8(int, const void *, int, void *, int, int, int);
extern void func_02088df8(int, const void *, int, void *, int, int, int, int, int, int, int, int);
extern const char data_ov142_0229c358[];
extern const char data_ov142_0229c368[];
extern const char data_ov142_0229c360[];
extern const char data_ov142_0229c370[];
extern const char data_ov142_0229c378[];
extern const char data_ov142_0229c3b8[];
extern const char data_ov142_0229c398[];
extern const Cell data_ov142_0229c448[];
}

extern "C" int func_ov142_0229bf6c(UnkStruct_0229bf6c *s)
{
    char *d;
    char *e;
    int a;
    int t;
    int i, j, k;
    int m;
    int n;

    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(&s->unk_E8);
    }
    if (func_ov142_02299668(s, 1) == 0) {
        return 0;
    }
    func_ov002_0220ad18(&s->unk_194, s->unk_98);
    d = (char *) s->unk_94 + 0x60;
    if (func_ov142_02299668(s, 0x100) == 0) {
        s->sub14c.v2();
        if (func_ov142_02299668(s, 0x800) != 0) {
            a = 9;
        } else {
            a = 8;
        }
        e = d;
        if (func_ov142_02299668(s, 0x2000) != 0) {
            e = d + 2;
        }
        func_020896b8(1, data_ov142_0229c358, 0x80, e, a, 1, 0);
        if (func_ov142_02299668(s, 0x400) != 0) {
            a = 9;
        } else {
            a = 8;
        }
        e = d;
        if (func_ov142_02299668(s, 0x1000) != 0) {
            e = d + 2;
        }
        func_020896b8(1, data_ov142_0229c368, 0x80, e, a, 1, 0);
        func_020896b8(1, data_ov142_0229c360, 0x80, d, -1, 1, 0);
        func_020896b8(1, data_ov142_0229c370, 0x80, d, -1, 1, 0);
    }
    k = 0x10;
    for (i = 0; i < 9; i++, k -= 2) {
        if (i == s->unk_BD) {
            t = 6;
        } else {
            t = 7;
        }
        func_020896b8(1, &data_ov142_0229c448[k], 0x80, d, t, 1, 0);
        func_020896b8(1, &data_ov142_0229c448[k + 1], 0x80, d, t, 1, 0);
    }
    func_02088df8(1, data_ov142_0229c378, 0x80, d, s->unk_BF, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    e = d - (s->unk_9C & 0xf);
    func_ov142_0229a6d8(s);
    m = -1;
    if (s->unk_BC == s->unk_BE) {
        m = s->unk_B8 - s->unk_B4;
        if (m < 0 || m >= 9) {
            m = -1;
        }
    }
    n = s->unk_B4;
    for (j = 0; j < 9; j++) {
        if (n >= 0 && m == j) {
            func_02088df8(1, data_ov142_0229c3b8, 0x80, e, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            func_02088df8(1, data_ov142_0229c398, 0x80, e, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        n++;
        e += 0x10;
    }
    return 1;
}
