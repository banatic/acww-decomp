/* func_ov004_0221fcdc @ 0x0221fcdc, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern Vec3 *func_02095794(int a);
extern int func_0201c378(void *s, int a);
extern int func_0201c2c8(void *s, int a);
extern int func_020e8b4c(int a, int b);
extern void func_0201b458(Vec3 *out, void *s, Vec3 *v);
extern int func_020eaa2c(Vec3 *w, void *p);
extern void func_ov004_0221fdf4(void *s, int a);
extern int func_ov004_0221ef2c(void *s);
extern int func_ov004_0221ef70(void *s);

int func_ov004_0221fcdc(char *s)
{
    Vec3 v;
    Vec3 w;
    Vec3 *q;
    int a;
    int b;
    q = func_02095794(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    a = func_0201c378(s, 4);
    b = func_020e8b4c(*(short *) (s + 0x8e), func_0201c2c8(s, 4));
    func_0201b458(&w, s, &v);
    if (a > 0x3000 && func_020eaa2c(&w, s + 0x5c) != 0) {
        func_ov004_0221fdf4(s, 6);
    } else if (b > 0x2000) {
        func_ov004_0221fdf4(s, 5);
    }
    if (func_ov004_0221ef2c(s) != 0) {
        return 1;
    }
    func_ov004_0221ef70(s);
    return 1;
}
