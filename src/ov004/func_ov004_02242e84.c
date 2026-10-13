/* func_ov004_02242e84 @ 0x02242e84, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02242e84 {
    char unk_00[0x34];
    Vec3 dir;
    char unk_40[0x4c - 0x40];
    int unk_4C;
    char unk_50[0x170 - 0x50];
    unsigned char unk_170;
} UnkStruct_02242e84;

extern void func_ov004_02242df8(Vec3 *out, unsigned int k);
extern int func_020644cc(int a);

void func_ov004_02242e84(UnkStruct_02242e84 *self)
{
    unsigned char s, v;

    s = (unsigned char) self->unk_4C;
    if (s == 0 && self->unk_170 == 0) {
        v = 1;
        self->unk_170 = 1;
    } else if (s == 4 && self->unk_170 != 0) {
        v = 3;
        self->unk_170 = 0;
    } else if (func_020644cc(0x64) > 0x46 && s != 0 && s != 4) {
        if (self->unk_170 != 0) {
            v = s - 1;
            self->unk_170 = 0;
        } else {
            v = s + 1;
            self->unk_170 = 1;
        }
    } else {
        if (self->unk_170 != 0) {
            v = s + 1;
        } else {
            v = s - 1;
        }
    }
    self->unk_4C = v;
    func_ov004_02242df8(&self->dir, v);
}
