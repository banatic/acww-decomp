/* func_ov003_02216410 @ 0x02216410, 0x4e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_02216460(void *, int, void *);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

typedef struct {
    int a;
    int b;
} Pair;

int func_ov003_02216410(int a, int b, Pair *c, int d, short e)
{
    Pair pair;
    char obj[12];
    char out[16];
    int result;

    func_0200e92c(&obj);
    func_0200e90c(&obj, 0x4b, d, e);
    pair.a = c->a;
    pair.b = c->b;
    func_ov003_02216460(&out, b, &pair);
    result = func_0200e894(a, &obj);
    func_0200e91c(&obj);
    return result;
}
