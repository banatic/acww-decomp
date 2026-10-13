/* func_0203b334 @ 0x0203b334, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern Vec3 data_021fbee8;
extern short FX_SinCosTable_[];

extern void *func_02095794(int);
extern void *func_ov003_022196e0(int);
extern void func_020eaca0(void *out, void *a, void *b);
extern int func_020ea9c8(void *in);
extern int func_0200322c(void *a, void *b);
extern int FX_MulFunc(int a, int b);
extern void func_01ffcbb0(void *dst, void *src);
extern void func_0203bc50(void *self, Vec3 *p);
extern void func_0203be6c(void *self);
extern int func_0203c57c(void *self);
extern int func_0203c568(void *self);
extern int func_0203c548(void *self);
extern void func_0203bd84(void *self, void *c, int a, int b, int d);

void func_0203b334(void *self)
{
    Vec3 A;
    char buf1[12];
    char buf2[16];
    Vec3 *p1, *p2;
    int v, raw, k;

    A.x = data_021fbee8.x;
    A.y = data_021fbee8.y;
    A.z = data_021fbee8.z;

    p1 = func_02095794(4);
    p2 = func_ov003_022196e0(4);

    if (p1 != 0 && p2 != 0) {
        func_020eaca0(buf1, p1, p2);
        v = func_020ea9c8(buf1);
        raw = func_0200322c(p1, p2);
        v = FX_MulFunc(v, 0xb33);

        A.x = p1->x;
        A.y = p1->y;
        A.z = p1->z;

        k = (int) ((unsigned short) raw) >> 4;
        A.x += FX_MulFunc(v, FX_SinCosTable_[2 * k]);
        A.z += FX_MulFunc(v, FX_SinCosTable_[2 * k + 1]);
    }

    func_0203bc50(self, &A);
    func_0203be6c(self);
    func_01ffcbb0(buf2, self);

    {
        int r1 = func_0203c57c(self);
        int r2 = func_0203c568(self);
        int r3 = func_0203c548(self);
        func_0203bd84(self, buf2, r1, r2, r3);
    }
}
