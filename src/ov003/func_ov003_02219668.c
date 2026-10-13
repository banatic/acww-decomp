/* func_ov003_02219668 @ 0x02219668, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02219668;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern void MTX_MultVec43(const Vec3 *a, const UnkStruct_02219668 *b, Vec3 *c);

void func_ov003_02219668(UnkStruct_02219668 *obj, const Vec3 *target)
{
    int old_24;
    int old_28;
    int old_2c;
    UnkStruct_02219668 tmp;
    Vec3 arg;
    Vec3 out;

    old_24 = obj->unk_24;
    old_28 = obj->unk_28;
    old_2c = obj->unk_2C;

    obj->unk_2C = 0;
    obj->unk_28 = obj->unk_2C;
    obj->unk_24 = obj->unk_28;

    tmp = *obj;

    if (target == 0) {
        arg.x = 0x4cd;
        arg.y = 0;
        arg.z = 0;
    } else {
        arg.x = target->x;
        arg.y = target->y;
        arg.z = target->z;
    }

    MTX_MultVec43(&arg, &tmp, &out);

    obj->unk_24 = out.x + old_24;
    obj->unk_28 = out.y + old_28;
    obj->unk_2C = out.z + old_2c;
}
