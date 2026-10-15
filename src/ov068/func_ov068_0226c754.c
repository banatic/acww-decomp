/* func_ov068_0226c754 @ 0x0226c754, 0x66 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    Vec3 v;
} UnkStruct_0226c754;

extern int func_0203dff0(void);
extern UnkStruct_0226c754 *func_02096190(int size);
extern UnkStruct_0226c754 *func_0203dfac(void);
extern void func_020eaca0(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern void func_020eaaa8(Vec3 *dst, int scale);
extern void func_01ffd070(Vec3 *dst, const Vec3 *a, const Vec3 *b);
extern int func_020ea990(int v, const Vec3 *vec);

int func_ov068_0226c754(int a, int b, int c)
{
    if (func_0203dff0()) {
        UnkStruct_0226c754 *p1 = func_02096190(4);
        UnkStruct_0226c754 *p2 = func_0203dfac();
        if (p1 != 0 && p2 != 0) {
            Vec3 v1, v2;
            func_020eaca0(&v1, &p1->v, &p2->v);
            func_020eaaa8(&v1, 1);
            func_01ffd070(&v2, &p1->v, &v1);
            {
                int r = func_020ea990(b, &v2);
                if (r < 0) {
                    r = -r;
                }
                if (r <= c) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
