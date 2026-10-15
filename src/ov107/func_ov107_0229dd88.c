/* func_ov107_0229dd88 @ 0x0229dd88, 0x3a bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov107_0229d480(void *a);
extern void func_ov002_02207e80(void *a, int b, int c, int d);
extern int func_ov002_02207f60(void *a);

void func_ov107_0229dd88(void *a)
{
    if (func_ov002_02207f48(a, 0) != 0) {
        func_ov002_022080a0((void *) (a), 2);
        func_ov107_0229d480(a);
    }
    func_ov002_02207e80(a, 6, 0, ~0xF);
    *(unsigned int *) ((char *) a + 0x98) = func_ov002_02207f60(a);
}
