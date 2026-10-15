/* func_ov100_0229e4fc @ 0x0229e4fc, 0x50 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

struct Context {
    char pad_00[0x28c4];
    int value;
};

extern int func_ov002_02207f3c(struct Context *p, int a);
extern void func_020027f0(int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov100_0229c2a0(struct Context *p, int a);
extern void func_ov002_02207e80(struct Context *p, int a, int b, int c);
extern int func_ov002_02207f60(struct Context *p);

void func_ov100_0229e4fc(struct Context *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_ov002_022080a0((void *) (p), 5);
        func_ov100_0229c2a0(p, 1);
        func_ov100_0229c2a0(p, 2);
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
    }
    p->value = func_ov002_02207f60(p);
}
