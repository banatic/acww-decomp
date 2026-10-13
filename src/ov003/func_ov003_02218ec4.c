/* func_ov003_02218ec4 @ 0x02218ec4, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

typedef struct UnkStruct_02218ec4 {
    int data[3];
} UnkStruct_02218ec4;

typedef struct UnkStruct_02218ec4_2 {
    int data[3];
} UnkStruct_02218ec4_2;

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_02218f0c(UnkStruct_02218ec4_2 *, Vec2 *);
extern int func_0200e894(int, void *);
extern void func_0200e91c(void *);

int func_ov003_02218ec4(int a0, Vec2 *src, int a2, int a3)
{
    Vec2 pair;
    UnkStruct_02218ec4 obj;
    UnkStruct_02218ec4_2 out;
    int ret;

    func_0200e92c(&obj);
    func_0200e90c(&obj, 0x16, a2, a3);
    pair.x = src->x;
    pair.y = src->y;
    func_ov003_02218f0c(&out, &pair);
    ret = func_0200e894(a0, &obj);
    func_0200e91c(&obj);
    return ret;
}
