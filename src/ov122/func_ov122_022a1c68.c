/* func_ov122_022a1c68 @ 0x022a1c68, 0x60 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int v);
extern void func_0200277c(int v);
extern void func_0200284c(int a, int b, int c);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov122_022a1c68(char *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_0200277c(4);
        func_0200277c(3);
        func_0200284c(4, 0, 0);
        func_0200284c(3, 0, 0);
        func_ov002_022080a0((void *) (p), 5);
    } else {
        func_ov002_02207e80(p, 4, 0, 0);
        func_ov002_02207e80(p, 3, 0, 0);
        *(int *) (p + 0x98) = func_ov002_02207f60(p);
    }
}
