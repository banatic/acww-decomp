/* func_0203bd84 @ 0x0203bd84, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x168];
    Vec3 A;
    short sh;
    char pad_176[0x188 - 0x176];
    Vec3 B;
    Vec3 C;
    Vec3 D;
} UnkStruct_0203bd84;

extern void func_020ea78c(Vec3 *v, int s);
extern void func_020ea6e0(Vec3 *v, int a);
extern void func_01ffd070(Vec3 *dst, Vec3 *src, Vec3 *oth);
extern int func_0203f844(Vec3 *dst, Vec3 *src);
extern Vec3 *func_0203c59c(UnkStruct_0203bd84 *self);
extern void func_020ea634(Vec3 *v, int s);

extern Vec3 data_021c67d0;
extern Vec3 data_021c67b8;
extern int data_021c679c;

void func_0203bd84(UnkStruct_0203bd84 *self, Vec3 *src, int angle, int param, int gval)
{
    Vec3 v1, v2;
    int tmp;

    v1.x = 0;
    v1.y = 0;
    v1.z = gval;

    func_020ea78c(&v1, (short) -angle);
    func_020ea6e0(&v1, param);

    func_01ffd070(&v2, src, &v1);

    self->A.x = v2.x;
    self->A.y = v2.y;
    self->A.z = v2.z;

    tmp = func_0203f844(&self->B, src);

    func_0203f844(&self->C, func_0203c59c(self));

    self->D.x = 0;
    self->D.y = 0x1000;
    self->D.z = 0;

    func_020ea78c(&self->D, tmp);
    func_020ea634(&self->D, self->sh);

    data_021c67d0.x = src->x;
    data_021c67d0.y = src->y;
    data_021c67d0.z = src->z;

    {
        Vec3 *p = func_0203c59c(self);
        data_021c67b8.x = p->x;
        data_021c67b8.y = p->y;
        data_021c67b8.z = p->z;
    }

    data_021c679c = gval;
}
