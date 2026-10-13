/* func_ov103_0229dc60 @ 0x0229dc60, 0x3c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cfa0(int a);
extern int func_ov002_02207f48(int a, int b);
extern int func_ov002_022080a0(int a, int b);
extern int func_ov002_02207e80(int a, int b, int c, int d);
extern int func_ov002_02207f60(int a);

void func_ov103_0229dc60(int a)
{
    if (func_ov002_02207f48(a, 0)) {
        func_ov002_022080a0(a, 2);
        func_ov103_0229cfa0(a);
    }
    func_ov002_02207e80(a, 6, 0, 0);
    *(int *) ((char *) a + 0x2b8c) = func_ov002_02207f60(a);
}
