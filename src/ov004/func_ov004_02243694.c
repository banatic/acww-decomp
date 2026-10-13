/* func_ov004_02243694 @ 0x02243694, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02243694 {
    char unk_00[0x40];
    Vec3 unk_40;
    char unk_4C[0x9a - 0x4c];
    unsigned char unk_9A;
    char unk_9B[0xac - 0x9b];
    short unk_AC;
    char unk_AE[0x172 - 0xae];
    short unk_172;
    char unk_174[0x192 - 0x174];
    short ang;
    char unk_194[0x196 - 0x194];
    signed char unk_196;
} UnkStruct_02243694;

extern int func_ov004_02244be0(UnkStruct_02243694 *self, int mode);
extern void func_ov004_022435e0(UnkStruct_02243694 *self);
extern void func_ov004_02241084(UnkStruct_02243694 *self);
extern void func_ov004_02244c40(UnkStruct_02243694 *self);
extern int func_020644cc(int a);

void func_ov004_02243694(UnkStruct_02243694 *self)
{
    Vec3 *p;

    switch (self->unk_172) {
        case 0:
            func_ov004_02244be0(self, 0);
            func_ov004_022435e0(self);
            break;
        case 6:
            if (self->unk_196 == 0xa) {
                func_ov004_02241084(self);
            }
            func_ov004_02244c40(self);
            break;
        case 7:
            self->unk_172 = 0;
            if (self->unk_9A != 0) {
                self->ang = (short) (self->ang + self->unk_AC);
            }
            break;
        default:
            self->unk_9A = 0;
            self->unk_172 = 0;
            if (self->unk_196 == 0x33) {
                p = &self->unk_40;
                if (func_020644cc(0x64) > 0x32) {
                    p->x = 0xef00;
                    p->z = 0xc900;
                } else {
                    p->x = 0xf700;
                    p->z = 0x15200;
                }
                p->y = 0x1300;
            }
            break;
    }
}
