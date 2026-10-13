/* func_ov003_02225da0 @ 0x02225da0, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    volatile unsigned short id;
    Vec3 a;
    Vec3 b;
} UnkStruct_02225da0;

extern int func_0204c63c(UnkStruct_02225da0 *s);
extern int func_ov003_02225e00(void *a0, int k, Vec3 *va, void *a3, Vec3 *vb, short s1, short s2, short s3);

int func_ov003_02225da0(void *a0, int a1, Vec3 *a2, void *a3, Vec3 *a4, short s1, short s2, short s3)
{
    UnkStruct_02225da0 s;
    s.id = 0xfff1;
    s.id = (unsigned short) a1;
    s.a.x = a2->x;
    s.a.y = a2->y;
    s.a.z = a2->z;
    s.b.x = a4->x;
    s.b.y = a4->y;
    s.b.z = a4->z;
    return func_ov003_02225e00(a0, func_0204c63c(&s), &s.a, a3, &s.b, s1, s2, s3);
}
