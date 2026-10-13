/* func_ov133_0229c25c @ 0x0229c25c, 0x54 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int x);
extern void func_020027f0(int x);
extern void func_ov133_0229ad68(void *p, int x);
extern void func_ov002_022080a0(void *p, int x);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

struct Type {
    char pad_00[0x94];
    int unk_94;
};

void func_ov133_0229c25c(struct Type *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov133_0229ad68(p, 1);
        func_ov002_022080a0(p, 5);
    } else {
        func_ov002_02207e80(p, 4, 0, 0);
        func_ov002_02207e80(p, 6, 0, 0);
        p->unk_94 = func_ov002_02207f60(p);
    }
}
