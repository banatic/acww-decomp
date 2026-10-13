/* func_ov003_02213d18 @ 0x02213d18, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef struct UnkStruct_02213d18 {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[4];
    unsigned int unk_2E0;
    char pad_2E4[0x68c - 0x2e0 - 4];
    int unk_68C;
    int unk_690;
    int unk_694;
} UnkStruct_02213d18;

extern int func_ov003_02213ec0(UnkStruct_02213d18 *self);
extern void func_0203f7d0(Vec3 *dst, Vec3 *src);
extern void func_ov003_02214200(UnkStruct_02213d18 *self, Vec3 *in, Vec3 *out1, Vec3 *out2);
extern void func_ov003_02213da0(UnkStruct_02213d18 *self, Vec3 *in, Vec3 *out1, Vec3 *out2);

void func_ov003_02213d18(UnkStruct_02213d18 *self)
{
    int x0, y0, z0;
    Vec3 v0, v1, out1, out2, v2;

    if (self->unk_2E0 == 0) {
        return;
    }
    if (((self->unk_2D8 << 4) >> 16) < 3) {
        return;
    }
    if (func_ov003_02213ec0(self) != 0) {
        return;
    }

    z0 = self->unk_694;
    y0 = self->unk_690;
    x0 = self->unk_68C;
    v0.x = x0;
    v0.y = y0;
    v0.z = z0;

    func_0203f7d0(&v0, &v0);

    v1.x = v0.x;
    v1.y = v0.y;
    v1.z = v0.z;

    func_ov003_02214200(self, &v1, &out1, &out2);

    v2.x = v0.x;
    v2.y = v0.y;
    v2.z = v0.z;

    func_ov003_02213da0(self, &v2, &out1, &out2);
}
