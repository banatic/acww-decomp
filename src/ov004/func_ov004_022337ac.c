/* func_ov004_022337ac @ 0x022337ac, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct Rec {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned short unk_0A;
    int unk_0C;
    unsigned char pad_10[0x14];
    int unk_24;
    int unk_28;
    int unk_2C;
    unsigned char pad_30[0x1c];
    unsigned char unk_4C[0x41];
    unsigned char unk_8D;
    unsigned char pad_8E[6];
} Rec;

typedef struct {
    int x, y, z;
} Vec3;

extern void func_ov004_0223383c(Rec *r);
extern void func_020044d0(void *self, const Vec3 *v);

void func_ov004_022337ac(Rec *r)
{
    volatile unsigned short h = 0xfff1;
    Vec3 v;
    int i;

    for (i = 0; i < 15; r++, i++) {
        if (r->unk_04 == 2) {
            r->unk_8D++;
            h = r->unk_08;
            if (r->unk_0C == 0) {
                func_ov004_0223383c(r);
            }
            v.x = r->unk_24;
            v.y = r->unk_28;
            v.z = r->unk_2C;
            func_020044d0(r->unk_4C, &v);
        }
    }
}
