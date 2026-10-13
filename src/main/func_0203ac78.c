/* func_0203ac78 @ 0x0203ac78, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short a;
    short b;
    int c[7];
} B32;
typedef struct {
    int x, y, z;
} C12;
typedef struct {
    unsigned char pad_00[0xfc];
    B32 sub;
    unsigned char pad_11C[0x4c];
    C12 other;
} UnkStruct_0203ac78;
extern UnkStruct_0203ac78 *data_021c67a4;
extern B32 data_021c6800;
extern C12 data_021c67f4;

void func_0203ac78(void)
{
    UnkStruct_0203ac78 *p = data_021c67a4;
    B32 *d = &p->sub;
    d->a = data_021c6800.a;
    d->b = data_021c6800.b;
    d->c[0] = data_021c6800.c[0];
    d->c[1] = data_021c6800.c[1];
    d->c[2] = data_021c6800.c[2];
    d->c[3] = data_021c6800.c[3];
    d->c[4] = data_021c6800.c[4];
    d->c[5] = data_021c6800.c[5];
    d->c[6] = data_021c6800.c[6];
    {
        C12 *o = &data_021c67a4->other;
        o->x = data_021c67f4.x;
        o->y = data_021c67f4.y;
        o->z = data_021c67f4.z;
    }
}
