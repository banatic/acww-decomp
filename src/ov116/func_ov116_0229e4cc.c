/* func_ov116_0229e4cc @ 0x0229e4cc, 0x3e bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *obj, int x);
extern void func_ov090_022993cc(int r, unsigned char c);
extern void func_ov002_022080a0(void *obj, int v);

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
} Object;

int func_ov116_0229e4cc(Object *obj, int x)
{
    int r;
    r = func_020ee45c(obj, x);
    if (x != -1 && x != 3) {
        func_ov090_022993cc(r, (unsigned char) x);
        obj->unk_8C = 2;
        func_ov002_022080a0(obj, 1);
        return 1;
    }
    return 0;
}
