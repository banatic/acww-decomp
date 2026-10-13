/* func_ov004_02245590 @ 0x02245590, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct UnkStruct_02245590 {
    int x, y, z;
    int unk_0C;
    short unk_10;
    short unk_12;
    int unk_14;
    unsigned char unk_18;
    unsigned char unk_19;
} UnkStruct_02245590;
extern int FX_Div(int a, int b);
extern int func_020e8b4c(int a, int b);
void func_ov004_02245590(UnkStruct_02245590 *o, Vec3 *src, int mask, int k, short a4, int a5, unsigned char a6)
{
    int best;
    int n;
    int sum;
    unsigned int i;
    int v;
    int last;
    // ENDDECLS
    o->x = src->x;
    o->y = src->y;
    o->z = src->z;
    o->unk_19 = (unsigned char) k;
    o->unk_12 = a4;
    o->unk_14 = a5;
    o->unk_18 = a6;
    sum = 0;
    n = 0;
    last = 0;
    for (i = 0; i < 4; i++) {
        if (((mask >> i) & 1) != 0) {
            sum = sum + (i << 14);
            last = (short) (i << 14);
            n++;
        }
    }
    o->unk_10 = (short) (FX_Div(sum << 12, n << 12) >> 12);
    if (n == 2) {
        if (func_020e8b4c(last, o->unk_10) >= 0x4000) {
            o->unk_10 = (short) (o->unk_10 + 0x8000);
        }
    }
    best = 0;
    for (i = 0; i < 4; i++) {
        if (((mask >> i) & 1) != 0) {
            v = func_020e8b4c((short) (i << 14), o->unk_10);
            if (v > best) {
                best = v;
            }
        }
    }
    o->unk_0C = best + 0x1300;
}
