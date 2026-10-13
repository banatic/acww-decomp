/* func_ov003_022351c4 @ 0x022351c4, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern void *func_0200322c(void *a);
extern void func_020e8870(short *a, void *b, int c);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *c);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *c);
extern void func_ov003_022321b8(Vec3 *dst, const Vec3 *src, int t);

void func_ov003_022351c4(char *self, const Vec3 *v, int t)
{
    short a = *(short *) (self + 0x23a);
    Vec3 d;
    char *o;
    d.x = v->x;
    d.y = v->y;
    d.z = v->z;
    o = self + 0x204;
    func_020e8870(&a, func_0200322c(o), t);
    *(short *) (self + 0x23a) = a;
    VEC_Subtract(&d, (Vec3 *) o, &d);
    func_ov003_022321b8(&d, &d, 1);
    VEC_Add((Vec3 *) o, &d, (Vec3 *) o);
}
