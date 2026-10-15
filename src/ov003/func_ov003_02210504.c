/* func_ov003_02210504 @ 0x02210504, 0xe8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern int func_0203f7d0(void *a, void *b);
extern int func_020912d4(int a, void *v, void *p, int d);
extern void func_02091278(void *, void *, void *, void *);
extern int func_0200f328(void *self, int a);
extern void func_0200fa6c(void *out, void *self);
extern int func_0200ff28(void *self, void *v, int a, int b);
extern void func_0209129c(int id);

typedef struct {
    int x, y, z;
} Vec3;

extern unsigned char data_ov003_02260540;
extern Vec3 data_ov003_02260558;

typedef struct {
    char pad_00[0x8e];
    unsigned char unk_8E;
    char pad_8F[0x2d8 - 0x8f];
    unsigned int unk_2D8;
    char pad_2DC[0x62c - 0x2dc];
    Vec3 unk_62C;
    char pad_638[0x7d4 - 0x638];
    int unk_7D4;
} UnkStruct_02210504;

void func_ov003_02210504(UnkStruct_02210504 *self)
{
    Vec3 v, a, b;
    int k;
    int *pid;
    int tx, ty, tz;

    func_02010f5c(self);
    k = (int) ((self->unk_2D8 << 4) >> 16);
    pid = &self->unk_7D4;
    if (k >= 5 && k <= 0x23) {
        tz = self->unk_62C.z;
        ty = self->unk_62C.y;
        tx = self->unk_62C.x;
        v.x = tx;
        v.y = ty;
        v.z = tz;
        func_0203f7d0(&v, &v);
        if (*pid == -1) {
            *pid = func_020912d4(0x26, &v, &self->unk_8E, 0);
            func_0200f328(self, 0x854);
            func_0200fa6c(&a, self);
            data_ov003_02260540 = 1;
            data_ov003_02260558.x = a.x;
            data_ov003_02260558.y = a.y;
            data_ov003_02260558.z = a.z;
        } else {
            func_02091278((void *) (*pid), (void *) (&v), (void *) (0), 0);
        }
        switch (k) {
            case 0x14:
                func_0200fa6c(&b, self);
                v.x = b.x;
                v.y = b.y;
                v.z = b.z;
                func_0200ff28(self, &v, 1, 5);
                break;
            case 0x23:
                if (*pid != -1) {
                    func_0209129c(*pid);
                    *pid = -1;
                }
                break;
        }
    }
}
