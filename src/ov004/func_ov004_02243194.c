/* func_ov004_02243194 @ 0x02243194, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02243194 {
    char unk_00[0xac];
    short unk_AC;
    char unk_AE[0x172 - 0xae];
    short unk_172;
    int unk_174;
    char unk_178[0x192 - 0x178];
    short ang;
} UnkStruct_02243194;

extern void func_ov004_02241ba8(UnkStruct_02243194 *self);
extern int func_ov004_02244e38(UnkStruct_02243194 *self, Vec3 *p);
extern int func_ov004_0224105c(int a);
extern int func_020644cc(int a);
extern void func_02090c2c(int a, Vec3 *b, int c, void *d);
extern int func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(int a, int b, int c);

extern unsigned char data_020e25d4[];
extern unsigned char data_ov004_02259a24;

void func_ov004_02243194(UnkStruct_02243194 *self, short *p)
{
    short *h;
    short v;

    h = (short *) ((char *) self + 0x98);
    if (*h > 0) {
        *h = (short) (*h - 1);
        func_ov004_02241ba8(self);
        func_ov004_02244e38(self, (Vec3 *) ((char *) self + 0x2c8));
        if (*h > 5) {
            if (data_ov004_02259a24 % 8 == 0 && func_020644cc(0x64) > 0x32) {
                v = self->ang;
                self->unk_AC = (short) (v + func_ov004_0224105c(0xc));
                self->unk_172 = 3;
            }
        } else if (*h == 5) {
            func_02090c2c(0x80, (Vec3 *) ((char *) self + 0x2c8), 0, (void *) data_020e25d4);
        }
    } else {
        self->unk_172 = 0x10;
        NNS_G3dMdlSetMdlAlpha(func_0209d088((char *) self + 0x288), 0, 0);
        self->unk_174 = 0x3c;
        *p = 0;
    }
}
