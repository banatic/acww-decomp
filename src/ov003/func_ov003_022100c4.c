/* func_ov003_022100c4 @ 0x022100c4, 0x4e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);
extern void func_ov003_02210114(void *, void *, int);

struct Pair {
    int a;
    int b;
};
struct UnkStruct_022100c4 {
    int a;
    int b;
    int c;
};

int func_ov003_022100c4(void *a1, struct Pair *a2, int a3, int a4, short a5)
{
    struct Pair pair;
    struct UnkStruct_022100c4 s12;
    char out[16];
    int ret;

    func_0200e92c(&s12);
    func_0200e90c(&s12, 0x66, a4, a5);
    pair.a = a2->a;
    pair.b = a2->b;
    func_ov003_02210114(out, &pair, a3);
    ret = func_0200e894(a1, &s12);
    func_0200e91c(&s12);
    return ret;
}
