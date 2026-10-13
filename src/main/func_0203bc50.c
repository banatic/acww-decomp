/* func_0203bc50 @ 0x0203bc50, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern void func_020eaca0(void *out, void *a, void *b);
extern int func_020ea9c8(void *in);
extern int func_020ea838(void *in);
extern int FX_MulFunc(int a, int b);
extern int func_0203c558(void *self);

typedef struct {
    char pad_00[0x110];
    Vec3 pos;
} UnkStruct_0203bc50;

void func_0203bc50(UnkStruct_0203bc50 *self, Vec3 *p)
{
    Vec3 d;
    int v;

    self->pos.y = p->y;
    func_020eaca0(&d, &self->pos, p);
    v = func_020ea9c8(&d);
    if (v > func_0203c558(self)) {
        v -= func_0203c558(self);
        if (func_020ea838(&d) != 0) {
            self->pos.x -= FX_MulFunc(d.x, v);
            self->pos.z -= FX_MulFunc(d.z, v);
        }
    }
}
