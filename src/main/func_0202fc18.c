/* func_0202fc18 @ 0x0202fc18, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int head;
    Vec3 v[4];
    int result;
} UnkStruct_0202fc18;
extern int func_0202fb60(UnkStruct_0202fc18 *out);

int func_0202fc18(UnkStruct_0202fc18 *out, Vec3 *a, Vec3 *b, Vec3 *c, Vec3 *d)
{
    out->v[0].x = a->x;
    out->v[0].y = a->y;
    out->v[0].z = a->z;
    out->v[1].x = b->x;
    out->v[1].y = b->y;
    out->v[1].z = b->z;
    out->v[2].x = c->x;
    out->v[2].y = c->y;
    out->v[2].z = c->z;
    out->v[3].x = d->x;
    out->v[3].y = d->y;
    out->v[3].z = d->z;
    out->result = func_0202fb60(out);
    return 1;
}
