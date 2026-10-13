/* func_02038758 @ 0x02038758, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    unsigned char pad_00[0xc8];
    unsigned char c8;
} UnkStruct_02038758;
typedef struct {
    unsigned char pad_00[0x7c];
    unsigned int unk_7C;
} UnkStruct_02038758_2;
typedef struct {
    unsigned char pad_00[0x40];
    Vec3 a, b, c;
} UnkStruct_02038758_3;

extern void G3i_PerspectiveW_(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f,
                              unsigned int g, void *h);
extern void G3i_LookAt_(Vec3 *a, Vec3 *b, Vec3 *c, int d, void *e);
extern int FX_MulFunc(int a, int b);
extern void func_02055e7c(void *p, Vec3 *v);
extern Vec3 data_021fbee8;

extern UnkStruct_02038758_2 data_027e0148;
extern UnkStruct_02038758_3 data_027e02c8;
extern char data_027e00d0[];
extern char data_027e0114[];
#define REG (&data_027e0148)
#define BLK (&data_027e02c8)

void func_02038758(UnkStruct_02038758 *self)
{
    Vec3 pos;
    Vec3 tgt;
    Vec3 up;
    Vec3 scale;
    int m;

    if (self->c8 == 0) {
        return;
    }
    G3i_PerspectiveW_(0x424, 0xf74, 0x1548, 0xf6, 0x0003e800, 0x1000, 0, data_027e00d0);
    REG->unk_7C = REG->unk_7C & ~0x50;
    pos.x = data_021fbee8.x;
    pos.y = data_021fbee8.y;
    pos.z = data_021fbee8.z;
    tgt.x = 0;
    tgt.y = 0;
    tgt.z = 0xfffff000;
    up.x = 0;
    up.y = 0x1000;
    up.z = 0;
    BLK->a.x = pos.x;
    BLK->a.y = pos.y;
    BLK->a.z = pos.z;
    BLK->b.x = up.x;
    BLK->b.y = up.y;
    BLK->b.z = up.z;
    BLK->c.x = tgt.x;
    BLK->c.y = tgt.y;
    BLK->c.z = tgt.z;
    G3i_LookAt_(&pos, &up, &tgt, 0, data_027e0114);
    REG->unk_7C = REG->unk_7C & ~0xe8;
    m = FX_MulFunc(0xb7, 0xf6d);
    scale.x = m;
    scale.y = m;
    scale.z = 0x1000;
    func_02055e7c((char *) self + 4, &scale);
}
