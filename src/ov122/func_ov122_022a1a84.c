/* func_ov122_022a1a84 @ 0x022a1a84, 0x3e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229fedc(void *p);
extern unsigned char *func_ov122_022a0018(void *p);
extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

int func_ov122_022a1a84(void *p)
{
    int result;
    int zero = 0;
    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov122_0229fedc(p);
        func_ov002_022080a0((void *) (p), 2);
        func_ov122_022a0018(p);
    }
    func_ov002_02207e80(p, 6, zero, zero);
    result = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x94) = result;
    return result;
}
