/* func_0203b4fc @ 0x0203b4fc, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern Vec3 data_021fbee8;
extern Vec3 *func_02095794(int a);
extern void func_0203be6c(void *self);
extern void func_01ffcbb0(void *dst, void *src);
extern int func_0203c57c(void *self);
extern int func_0203c568(void *self);
extern int func_0203c548(void *self);
extern void func_0203bd84(void *self, void *c, int a, int b, int d);
typedef struct {
    char pad_00[0x110];
    int unk_110, unk_114, unk_118;
} UnkStruct_0203b4fc;

void func_0203b4fc(UnkStruct_0203b4fc *self)
{
    volatile int A[3];
    char buf[16];
    Vec3 *p;
    int a, b, d;
    A[0] = data_021fbee8.x;
    A[1] = data_021fbee8.y;
    A[2] = data_021fbee8.z;
    p = func_02095794(4);
    if (p != 0) {
        A[0] = p->x;
        A[1] = p->y;
        A[2] = p->z;
    }
    self->unk_110 = A[0];
    self->unk_114 = A[1];
    self->unk_118 = A[2];
    func_0203be6c(self);
    func_01ffcbb0(buf, self);
    a = func_0203c57c(self);
    b = func_0203c568(self);
    d = func_0203c548(self);
    func_0203bd84(self, buf, a, b, d);
}
