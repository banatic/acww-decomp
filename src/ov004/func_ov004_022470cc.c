/* func_ov004_022470cc @ 0x022470cc, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_022470cc {
    char unk_00[0x110];
    Vec3 a;
    char unk_11C[0x1cc - 0x11c];
    Vec3 b;
    int unk_1D8;
} UnkStruct_022470cc;

extern int func_02095794(int a);
extern void func_01ffd070(Vec3 *out, void *a, Vec3 *b);
extern void func_020eaad0(Vec3 *out, Vec3 *in, int n);
extern void func_0203be6c(UnkStruct_022470cc *self);
extern void func_01ffcbb0(Vec3 *out, UnkStruct_022470cc *self);
extern int func_0203c57c(UnkStruct_022470cc *self);
extern int func_0203c568(UnkStruct_022470cc *self);
extern int func_0203c548(UnkStruct_022470cc *self);
extern void func_0203bd84(UnkStruct_022470cc *self, Vec3 *v, int a, int b, int c);

void func_ov004_022470cc(UnkStruct_022470cc *self)
{
    Vec3 t, u, v;
    int *p;
    int d;
    void *o;

    o = (void *) func_02095794(4);
    func_01ffd070(&t, o, &self->b);
    func_020eaad0(&u, &t, 1);
    self->a.x = u.x;
    self->a.y = u.y;
    self->a.z = u.z;
    d = ((int *) o)[2] - *(int *) ((char *) self + 0x1d4);
    if (d < 0) {
        d = -d;
    }
    p = (int *) ((char *) self + 0x118);
    *p = *p + (d >> 1);
    func_0203be6c(self);
    func_01ffcbb0(&v, self);
    func_0203bd84(self, &v, func_0203c57c(self), func_0203c568(self), func_0203c548(self));
}
