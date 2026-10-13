/* func_020bc1bc @ 0x020bc1bc, 0x1c4 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int unk_00, unk_04;
} UnkStruct_020bc1bc_3;

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0x10 - 8];
    char unk_10[0x31 - 0x10];
    unsigned char unk_31;
    char pad_32[0x34 - 0x32];
    UnkStruct_020bc1bc_3 unk_34;
    char pad_3C[0x4c - 0x3c];
    int unk_4C;
    int unk_50;
    unsigned short unk_54;
    unsigned char unk_56, unk_57;
    int unk_58;
    unsigned char unk_5C;
    signed char unk_5D;
    char pad_5E[0x74 - 0x5e];
} UnkStruct_020bc1bc;

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
} UnkStruct_020bc1bc_2;

extern UnkStruct_020bc1bc_2 data_021f8ab0;
extern int data_021f8ac4[];
extern int data_021f75b0;
extern int func_0208a1d0(void *p);
extern int func_0208a1b0(void *p, int x);
extern int func_0208a198(void *p, int x);
extern void func_02088df8(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

void func_020bc1bc(void *self)
{
    UnkStruct_020bc1bc *p;
    UnkStruct_020bc1bc *end;
    int K;
    int neg1;
    void *o;
    UnkStruct_020bc1bc_3 *sb;
    int A, B, X, Y, Yr;
    int h, ok;
    int lo, hi;

    end = (UnkStruct_020bc1bc *) ((char *) self + 0x1b30);
    K = data_021f8ac4[data_021f8ab0.unk_1C ^ 1];
    neg1 = -1;
    for (p = (UnkStruct_020bc1bc *) self; p < end; p = (UnkStruct_020bc1bc *) ((char *) p + 0x74)) {
        if (p->unk_00 == 0xd) {
            continue;
        }
        if (p->unk_04 != 2) {
            continue;
        }
        if (p->unk_31 != 0) {
            continue;
        }
        o = &p->unk_10[0];
        A = func_0208a1d0(o);
        if (A == 0) {
            continue;
        }
        sb = &p->unk_34;
        B = func_0208a1b0(o, neg1);
        Yr = func_0208a198(o, neg1);
        X = B + ((sb->unk_00 + 0x800) >> 12);
        Yr = Yr + ((sb->unk_04 + 0x800) >> 12);
        Y = Yr - K;
        if (data_021f75b0 == 1) {
            h = p->unk_5C;
            ok = 0;
            if (h != 0) {
                lo = Y - h;
                hi = Y + h;
                if (hi < 0 || lo > 0xbf) {
                    ok = 1;
                }
            }
            if (ok != 0) {
                continue;
            }
            func_02088df8(0, A, X, Y, p->unk_5D, p->unk_58, p->unk_4C, p->unk_50, p->unk_54, neg1,
                          (unsigned char) (signed char) p->unk_56, (unsigned char) (signed char) p->unk_57);
        } else if (Yr < 0xc0) {
            h = p->unk_5C;
            ok = 0;
            if (h != 0) {
                lo = Y - h;
                hi = Y + h;
                if (hi < 0 || lo > 0xbf) {
                    ok = 1;
                }
            }
            if (ok != 0) {
                continue;
            }
            func_02088df8(1, A, X, Y, p->unk_5D, p->unk_58, p->unk_4C, p->unk_50, p->unk_54, neg1, p->unk_56, p->unk_57);
        } else if (Yr > 0x100) {
            Y = Y - 0x100;
            h = p->unk_5C;
            ok = 0;
            if (h != 0) {
                lo = Y - h;
                hi = Y + h;
                if (hi < 0 || lo > 0xbf) {
                    ok = 1;
                }
            }
            if (ok != 0) {
                continue;
            }
            func_02088df8(0, A, X, Y, p->unk_5D, p->unk_58, p->unk_4C, p->unk_50, p->unk_54, neg1,
                          (unsigned char) (signed char) p->unk_56, (unsigned char) (signed char) p->unk_57);
        }
    }
}
