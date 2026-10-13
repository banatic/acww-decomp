/* func_0203b684 @ 0x0203b684, 0x14c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x110];
    int unk_110, unk_114, unk_118;
    char pad_11C[0x1f4 - 0x11c];
    unsigned char unk_1F4;
    char pad_1F5[0x1fc - 0x1f5];
    int unk_1FC;
} UnkStruct_0203b684;

extern Vec3 data_021fbee8;
extern Vec3 *func_02095794(int a);
extern void func_0203be6c(void *self);
extern void func_01ffcbb0(void *dst, void *src);
extern Vec3 *func_0203c59c(void *self);
extern int func_0203ad88(void);
extern int func_0203c548(void *self);
extern int func_0203c57c(void *self);
extern int func_0203c568(void *self);
extern void func_020ea78c(Vec3 *v, short a);
extern void func_020ea6e0(Vec3 *v, int a);
extern void func_01ffd070(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int func_0206fd34(void);
extern int func_ov068_0226dabc(void *self);
extern void func_0203bcc4(void *self, Vec3 *a, Vec3 *b);
extern void func_0203bd84(void *self, void *c, int a, int b, int d);

void func_0203b684(UnkStruct_0203b684 *self)
{
    volatile int A[3];
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Vec3 d;
    Vec3 e;
    Vec3 *p;
    int i, j, k;
    int z0;

    A[0] = data_021fbee8.x;
    A[1] = data_021fbee8.y;
    A[2] = data_021fbee8.z;
    p = func_02095794(4);
    if (p != 0) {
        A[0] = p->x;
        A[1] = p->y;
        A[2] = p->z;
    }
    if (self->unk_1F4 == 0) {
        func_0203be6c(self);
        func_01ffcbb0(&a, self);
        p = func_0203c59c(self);
        b.x = p->x;
        b.y = p->y;
        b.z = p->z;
        if (func_0203ad88() != 0) {
            z0 = func_0203c548(self);
            c.x = 0;
            c.y = 0;
            c.z = z0;
            func_020ea78c(&c, (short) -func_0203c57c(self));
            func_020ea6e0(&c, func_0203c568(self));
            func_01ffd070(&d, &a, &c);
            b.x = d.x;
            b.y = d.y;
            b.z = d.z;
        }
        a.y = a.y + (0x1000 - func_0206fd34()) * 15;
        b.y = b.y + (0x1000 - func_0206fd34()) * 2;
        if (self->unk_1FC == 9) {
            a.y = a.y + func_ov068_0226dabc(self);
        }
        func_0203bcc4(self, &a, &b);
    } else {
        self->unk_110 = A[0];
        self->unk_114 = A[1];
        self->unk_118 = A[2];
        func_0203be6c(self);
        func_01ffcbb0(&e, self);
        i = func_0203c57c(self);
        j = func_0203c568(self);
        k = func_0203c548(self);
        func_0203bd84(self, &e, i, j, k);
    }
}
