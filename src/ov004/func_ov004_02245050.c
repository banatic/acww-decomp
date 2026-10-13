/* func_ov004_02245050 @ 0x02245050, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02245050 {
    char unk_00[0x178];
    Vec3 arm[2];
    char unk_190[0x192 - 0x190];
    short ang;
    char unk_194[0x2cc - 0x194];
    int posy;
} UnkStruct_02245050;

extern void func_02032c64(void *ctx);
extern void func_02032c50(void *ctx);
extern void func_02031288(void *ctx, Vec3 *a, Vec3 *b, int ang, int r, void *o, int k);

int func_ov004_02245050(UnkStruct_02245050 *self)
{
    char buf[0x30];
    unsigned char n;
    Vec3 *q;
    int y;
    short ang;

    n = 0;
    q = self->arm;
    y = self->posy;
    func_02032c64(buf);
    ang = self->ang;
    func_02031288(buf, q, q, ang, 0x266, 0, 0xb);
    if (q[0].y > y) {
        n = n + 1;
    }
    func_02031288(buf, &q[1], &q[1], ang, 0x266, 0, 0xb);
    if (q[1].y > y) {
        n = n + 2;
    }
    func_02032c50(buf);
    return n;
}
