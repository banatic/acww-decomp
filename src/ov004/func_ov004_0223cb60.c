/* func_ov004_0223cb60 @ 0x0223cb60, 0x56 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    long x, y, z;
} UnkStruct_0223cb60;
typedef struct {
    long id;
    UnkStruct_0223cb60 a;
    UnkStruct_0223cb60 b;
    long unk_1C;
    UnkStruct_0223cb60 c;
    UnkStruct_0223cb60 d;
    short unk_38;
    short pad_3A;
    long unk_3C;
} UnkStruct_0223cb60_2;
void func_ov004_0223cb60(UnkStruct_0223cb60_2 *out, long id, UnkStruct_0223cb60 *a, UnkStruct_0223cb60 *b, long e,
                         UnkStruct_0223cb60 *c, UnkStruct_0223cb60 *d, short g, long h)
{
    if (id == -1) {
        return;
    }
    out->id = id;
    out->a.x = a->x;
    out->a.y = a->y;
    out->a.z = a->z;
    out->b.x = b->x;
    out->b.y = b->y;
    out->b.z = b->z;
    out->unk_1C = e;
    out->c.x = c->x;
    out->c.y = c->y;
    out->c.z = c->z;
    out->d.x = d->x;
    out->d.y = d->y;
    out->d.z = d->z;
    out->unk_38 = g;
    out->unk_3C = h;
}
