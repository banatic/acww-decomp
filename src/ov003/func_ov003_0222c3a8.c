/* func_ov003_0222c3a8 @ 0x0222c3a8, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x4c];
    Vec3 unk_4C;
    char pad_58[8];
} UnkStruct_0222c3a8;
extern UnkStruct_0222c3a8 data_ov003_0225f35c[];
void func_ov003_0222c3a8(Vec3 *src, int i)
{
    UnkStruct_0222c3a8 *e;
    Vec3 *q;
    if (i >= 0 && i < 4) {
        e = &data_ov003_0225f35c[i];
        q = &e->unk_4C;
        q->x = src->x;
        q->y = src->y;
        q->z = src->z;
    }
}
