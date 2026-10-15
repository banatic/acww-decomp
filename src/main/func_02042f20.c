/* func_02042f20 @ 0x02042f20, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} Pair;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
    int unk_14;
    int unk_18;
    unsigned char unk_1C;
    unsigned char unk_1D;
    signed char unk_1E;
    unsigned char pad_1F;
    int unk_20;
} Slot;

extern int func_0209a1d0(void);
extern int func_02099fe8(void);
extern unsigned char func_020b65c4(void);
extern int func_020a6ff0(int);
extern void func_02045770(unsigned char i, int p1);

int func_02042f20(Slot *slot, int a1, int a2, Pair *a3, unsigned short p5, unsigned short p6, unsigned char p7,
                  unsigned char p8, int p9, signed char p10)
{
    int i;
    int r;
    int va, vb;

    r = -1;
    for (i = 0; i < 3; slot++, i++) {
        if (slot->unk_08 != 0 || slot->unk_0C != 0) {
            continue;
        }
        if (a2 == 3 || a2 == 9 || a2 == 0x15) {
            if (p6 == 0x1520) {
                if (func_0209a1d0() == 0) {
                    a2++;
                }
            } else {
                if (func_02099fe8() < 0) {
                    a2++;
                }
            }
        }
        slot->unk_00 = a1;
        slot->unk_04 = func_020a6ff0((int) func_020b65c4());
        slot->unk_08 = 1;
        slot->unk_0C = a2;
        slot->unk_10 = p5;
        slot->unk_12 = p6;
        va = a3->a;
        vb = a3->b;
        slot->unk_14 = va;
        slot->unk_18 = vb;
        slot->unk_1C = p8;
        slot->unk_1D = p7;
        slot->unk_20 = p9;
        slot->unk_1E = p10;
        func_02045770((unsigned char) i, p9);
        r = i;
        break;
    }
    return r;
}
