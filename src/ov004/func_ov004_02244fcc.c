/* func_ov004_02244fcc @ 0x02244fcc, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02244fcc {
    char unk_00[0x2c8];
    Vec3 pos;
} UnkStruct_02244fcc;

extern short FX_SinCosTable_[];

void func_ov004_02244fcc(UnkStruct_02244fcc *self)
{
    Vec3 *p, *q;
    short ang;
    int i, x, y, z;

    p = &self->pos;
    ang = *(short *) ((char *) self + 0x192);
    q = (Vec3 *) ((char *) self + 0x178);
    i = ((unsigned short) (short) (ang + 0xe38) >> 4) << 1;
    z = p->z + FX_SinCosTable_[i + 1];
    y = p->y;
    x = p->x + FX_SinCosTable_[i];
    q[0].x = x;
    q[0].y = y;
    q[0].z = z;
    i = ((unsigned short) (short) (ang - 0xe38) >> 4) << 1;
    z = p->z + FX_SinCosTable_[i + 1];
    y = p->y;
    x = p->x + FX_SinCosTable_[i];
    q[1].x = x;
    q[1].y = y;
    q[1].z = z;
}
