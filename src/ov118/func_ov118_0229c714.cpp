/* func_ov118_0229c714 @ 0x0229c714, 0x290 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c714_3 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct UnkStruct_0229c714_2 {
    unsigned char a, b, c;
};

struct UnkStruct_0229c714 {
    char pad_00[0x94];
    char *unk_94;
    char pad_98[6];
    unsigned char unk_9E;
    unsigned char unk_9F;
    char pad_A0[4];
    unsigned char unk_A4;
    char pad_A5[4];
    unsigned char unk_A9;
    char pad_AA[3];
    unsigned char unk_AD;
    char pad_AE[3];
    unsigned char unk_B1;
    char pad_B2[0x5c6];
    UnkStruct_0229c714_3 sub678;
    char pad_67C[0x44];
    char unk_6C0;
    char pad_6C1[0x40e3];
    UnkStruct_0229c714_2 arrA[3];
    UnkStruct_0229c714_2 arrB[14];
};

extern "C" {
extern int func_ov118_0229a460(UnkStruct_0229c714 *, int);
extern void func_0208ea70(UnkStruct_0229c714_3 *, int, char *);
extern int func_0206fe54(void);
extern void *func_ov002_0220a4f8(UnkStruct_0229c714_3 *);
extern int func_ov002_0220a4d4(UnkStruct_0229c714_3 *);
extern void func_ov002_0220a0b4(void *, void *, int);
extern void func_ov002_02209eb8(void *);
extern void func_02088df8(int, const void *, int, void *, int, int, int, int, int, int, int, int);
extern void func_ov118_0229b27c(UnkStruct_0229c714 *, int, char *, int, int, int);
extern const char data_ov118_0229cbb0[];
extern const char data_ov118_0229cb70[];
extern const char data_ov118_0229cb90[];
}

extern "C" int func_ov118_0229c714(UnkStruct_0229c714 *s)
{
    char *d;
    int i;
    int m, n;
    int x, t;
    unsigned char c;
    void *h;

    d = s->unk_94 + 0x60;
    if (func_ov118_0229a460(s, 4) != 0) {
        if (func_ov118_0229a460(s, 8) != 0) {
            func_0208ea70(&s->sub678, 0x67, (s->unk_94 - 0x12) + s->unk_A4);
        }
        if (func_0206fe54() != 0) {
            if (func_ov118_0229a460(s, 0x1000) != 0) {
                h = func_ov002_0220a4f8(&s->sub678);
                func_ov002_0220a0b4(&s->unk_6C0, h, func_ov002_0220a4d4(&s->sub678));
            }
            func_ov002_02209eb8(&s->unk_6C0);
        }
        func_02088df8(1, data_ov118_0229cbb0, 0x80, d, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        if (func_ov118_0229a460(s, 1) != 0) {
            m = 0xc;
            n = 0xd;
        } else {
            m = 0xb;
            n = 0xe;
        }
        func_02088df8(1, data_ov118_0229cb70, 0x80, d, n, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(1, data_ov118_0229cb90, 0x80, d, m, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        if (func_0206fe54() != 0 && func_ov118_0229a460(s, 0x800) != 0 && s->unk_AD != 0xe && s->arrB[s->unk_AD].c != 0xc) {
            func_ov118_0229b27c(s, s->arrB[s->unk_AD].a, s->unk_94 + s->arrB[s->unk_AD].b, 0xb, 0, -1);
        }
        s->unk_B1 = (s->unk_B1 + 1) & 0xf;
        if ((s->unk_B1 & 0xc) != 0) {
            func_ov118_0229b27c(s, s->unk_9E, (char *) (s->unk_9F + (unsigned int) s->unk_94), 0xa, 0, -1);
        }
        for (i = 0; i < 3; i++) {
            c = s->arrA[i].c;
            if (c != 0xc) {
                if ((c & 0x80) != 0) {
                    x = 1;
                } else {
                    x = 0;
                }
                func_ov118_0229b27c(s, s->arrA[i].a, s->unk_94 + s->arrA[i].b, (unsigned char) (c & 0x7f), x, -1);
            }
        }
        for (i = 0; i < 14; i++) {
            if (s->arrB[i].c != 0xc) {
                if (i == s->unk_A9 && func_ov118_0229a460(s, 0x100) == 0) {
                    t = 8;
                } else {
                    t = -1;
                }
                func_ov118_0229b27c(s, s->arrB[i].a, s->unk_94 + s->arrB[i].b, s->arrB[i].c, 0, t);
            }
        }
        if (func_ov118_0229a460(s, 8) != 0) {
            s->sub678.v2();
        }
    }
    return 1;
}
