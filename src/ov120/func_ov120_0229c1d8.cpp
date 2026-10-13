/* func_ov120_0229c1d8 @ 0x0229c1d8, 0x248 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c1d8_3 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct UnkStruct_0229c1d8_2 {
    unsigned char a, b, c;
};

struct UnkStruct_0229c1d8 {
    char pad_00[0x94];
    char *unk_94;
    char pad_98[6];
    unsigned char unk_9E;
    unsigned char unk_9F;
    char pad_A0[4];
    unsigned char unk_A4;
    char pad_A5[3];
    unsigned char unk_A8;
    char pad_A9[3];
    unsigned char unk_AC;
    char pad_AD[2];
    unsigned char unk_AF;
    char pad_B0[0x5c4];
    UnkStruct_0229c1d8_3 sub674;
    char pad_678[0x44];
    char unk_6BC;
    char pad_6BD[0x207d];
    UnkStruct_0229c1d8_2 arrA[3];
    UnkStruct_0229c1d8_2 arrB[14];
};

extern "C" {
extern int func_ov120_0229a448(UnkStruct_0229c1d8 *, int);
extern void func_0208ea70(UnkStruct_0229c1d8_3 *, int, char *);
extern void func_ov002_02209eb8(void *);
extern void func_02088df8(int, const void *, int, void *, int, int, int, int, int, int, int, int);
extern void func_ov120_0229b06c(UnkStruct_0229c1d8 *, int, char *, int, int, int);
extern const char data_ov120_0229c5f8[];
extern const char data_ov120_0229c5b8[];
extern const char data_ov120_0229c5d8[];
}

extern "C" int func_ov120_0229c1d8(UnkStruct_0229c1d8 *s)
{
    char *d;
    int i;
    int m, n;
    int x, t;
    unsigned char c;

    d = s->unk_94 + 0x60;
    if (func_ov120_0229a448(s, 4) != 0) {
        if (func_ov120_0229a448(s, 8) != 0) {
            func_0208ea70(&s->sub674, 0x67, (s->unk_94 - 0x12) + s->unk_A4);
        }
        func_ov002_02209eb8(&s->unk_6BC);
        func_02088df8(1, data_ov120_0229c5f8, 0x80, d, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        if (func_ov120_0229a448(s, 1) != 0) {
            m = 0xc;
            n = 0xd;
        } else {
            m = 0xb;
            n = 0xe;
        }
        func_02088df8(1, data_ov120_0229c5b8, 0x80, d, n, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(1, data_ov120_0229c5d8, 0x80, d, m, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        if (s->unk_AC != 0xe && s->arrB[s->unk_AC].c != 0xc) {
            func_ov120_0229b06c(s, s->arrB[s->unk_AC].a, s->unk_94 + s->arrB[s->unk_AC].b, 0xb, 0, -1);
        }
        s->unk_AF = (s->unk_AF + 1) & 0xf;
        if ((s->unk_AF & 0xc) != 0) {
            func_ov120_0229b06c(s, s->unk_9E, (char *) (s->unk_9F + (unsigned int) s->unk_94), 0xa, 0, -1);
        }
        for (i = 0; i < 3; i++) {
            c = s->arrA[i].c;
            if (c != 0xc) {
                if ((c & 0x80) != 0) {
                    x = 1;
                } else {
                    x = 0;
                }
                func_ov120_0229b06c(s, s->arrA[i].a, s->unk_94 + s->arrA[i].b, (unsigned char) (c & 0x7f), x, -1);
            }
        }
        for (i = 0; i < 14; i++) {
            if (s->arrB[i].c != 0xc) {
                if (i == s->unk_A8 && func_ov120_0229a448(s, 0x100) == 0) {
                    t = 8;
                } else {
                    t = -1;
                }
                func_ov120_0229b06c(s, s->arrB[i].a, s->unk_94 + s->arrB[i].b, s->arrB[i].c, 0, t);
            }
        }
        if (func_ov120_0229a448(s, 8) != 0) {
            s->sub674.v2();
        }
    }
    return 1;
}
