/* func_ov050_022609f0 @ 0x022609f0, 0x76 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

extern int func_ov050_022604bc(void *self);
extern Vec3 *func_02095794(int a);
extern void *func_ov050_022609d8(void *self);
extern void *func_0200338c(void *a, int b);
extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int VEC_Mag(Vec3 *v);

int func_ov050_022609f0(unsigned char *self)
{
    Vec3 vecA;
    Vec3 vecB;
    Vec3 diff1, diff2;
    void *obj;
    int dist1, dist2;

    Vec3 *pA;
    Vec3 *pB;

    if (!func_ov050_022604bc(self)) {
        goto fail;
    }

    pA = func_02095794(4);
    vecA.x = pA->x;
    vecA.y = pA->y;
    vecA.z = pA->z;

    obj = func_ov050_022609d8(self);
    obj = func_0200338c(obj, 0);
    if (!obj) {
        goto fail;
    }

    pB = (Vec3 *) ((unsigned char *) obj + 0x5c);
    vecB.x = pB->x;
    vecB.y = pB->y;
    vecB.z = pB->z;

    func_020eaca0(&diff1, &vecA, &vecB);
    dist1 = VEC_Mag(&diff1);

    func_020eaca0(&diff2, &vecA, (Vec3 *) (self + 0x5c));
    dist2 = VEC_Mag(&diff2);

    if (dist2 < dist1) {
        return 1;
    }
fail:
    return 0;
}
