/* func_ov003_022122ac @ 0x022122ac, 0x4e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Pair;
typedef struct {
    char data[12];
} UnkStruct_022122ac;
typedef struct {
    char data[16];
} Result;

extern unsigned int func_0200e92c(UnkStruct_022122ac *);
extern void func_0200e90c(UnkStruct_022122ac *, int, void *, short);
extern void func_ov003_022122fc(Result *, Pair *, void *);
extern int func_0200e894(void *, UnkStruct_022122ac *);
extern int func_0200e91c(UnkStruct_022122ac *);

int func_ov003_022122ac(void *a, void *b, Pair *c, void *d, short e)
{
    Pair pair;
    UnkStruct_022122ac obj;
    Result result;
    int ret;

    func_0200e92c(&obj);
    func_0200e90c(&obj, 0x5d, d, e);

    pair.x = c->x;
    pair.y = c->y;

    func_ov003_022122fc(&result, &pair, b);

    ret = func_0200e894(a, &obj);
    func_0200e91c(&obj);

    return ret;
}
