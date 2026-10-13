/* func_ov004_0221fbf8 @ 0x0221fbf8, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern int func_ov004_0221ef2c(void *s);
extern int func_ov004_0221ef70(void *s);
extern Vec3 *func_02095794(int a);
extern int func_0201c378(void *s, int a);
extern int func_0201c2c8(void *s, int a);
extern void func_0201b458(Vec3 *out, void *s, Vec3 *v);
extern int func_020eaa2c(Vec3 *w, void *p);
extern void func_ov004_0221fdf4(void *s, int a);
extern void func_0201aff4(void *p, int a);
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);

int func_ov004_0221fbf8(char *s)
{
    Vec3 v;
    Vec3 w;
    Vec3 *q;
    int a;
    int b;
    if (func_ov004_0221ef2c(s) != 0) {
        return 1;
    }
    if (func_ov004_0221ef70(s) != 0) {
        return 1;
    }
    q = func_02095794(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    a = func_0201c378(s, 4);
    b = func_0201c2c8(s, 4);
    func_0201b458(&w, s, &v);
    if (a > 0x3000 && func_020eaa2c(&w, s + 0x5c) != 0) {
        func_ov004_0221fdf4(s, 6);
        return 1;
    }
    func_0201aff4(s + 0x350, b);
    if (func_02019e00(s + 0x564) == 3) {
        if (func_02019de8(s + 0x564) != 0) {
            func_ov004_0221fdf4(s, 4);
        }
    }
    return 1;
}
