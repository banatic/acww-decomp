/* func_02010ca4 @ 0x02010ca4, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

struct Self5 {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad_68[0x7f0 - 0x68];
    int unk_7F0;
    unsigned char pad_7F4[0x800 - 0x7f4];
    int unk_800;
};

extern void *data_020ccf94;

extern int func_02073908(void *a, int b);
extern int func_020b67ac(void);
extern int func_020b6590(void);
extern void *func_020b7d3c(int h, void *p1, Vec3 *p2, int a3, int a4, int a5, int a6);

int func_02010ca4(struct Self5 *self)
{
    Vec3 *p;
    Vec3 v;
    int h;

    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        int gate = func_020b67ac();
        if (gate == 0) {
            return gate;
        }
        if (self->unk_7F0 != 8) {
            return self->unk_7F0;
        }
    }

    p = (Vec3 *) ((char *) self + 0x5c);
    v.x = self->unk_5C;
    v.y = p->y;
    v.z = p->z;
    v.y = v.y + 0xb33;

    h = func_020b6590();
    return (int) func_020b7d3c(h, (char *) self + 0x214, &v, 0xa00, 0x15cf, 1, (unsigned char) self->unk_800);
}
