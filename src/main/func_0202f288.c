/* func_0202f288 @ 0x0202f288, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

struct UnkStruct_0202f288 {
    unsigned char pad_00[0x14];
    Vec2 vec;
};

extern int func_0202f660(struct UnkStruct_0202f288 *a, int b);
extern void func_0202f8fc(Vec2 *v, int a, int b);
extern int func_0202f520(struct UnkStruct_0202f288 *a, Vec2 *v, int b, int c);
extern void func_0202f874(Vec2 *v, int a);
extern void func_0202f8b4(int b, Vec2 *v);

int func_0202f288(struct UnkStruct_0202f288 *a, int b, int c, int d)
{
    Vec2 v;
    Vec2 w;
    Vec2 *q;

    if (func_0202f660(a, c) > 0) {
        func_0202f8fc(&v, 0, 0);
        if (func_0202f520(a, &v, b, c) != 0) {
            int diff = d - func_0202f660(a, b);
            if (diff < 0) {
                diff = -diff;
            }

            q = &a->vec;
            w.x = a->vec.x;
            w.y = q->y;

            func_0202f874(&w, diff);
            func_0202f8b4(b, &w);
            return 1;
        }
    }
    return 0;
}
