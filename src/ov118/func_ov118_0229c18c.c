/* func_ov118_0229c18c @ 0x0229c18c, 0x60 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int v);
extern void func_020027f0(int v);
extern void func_ov118_0229a440(void *p, int v);
extern void func_ov002_022080a0(void *p, int v);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov118_0229c18c(char *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov118_0229a440(p, 4);
        func_ov002_022080a0(p, 5);
    } else {
        unsigned short v;
        func_ov002_02207e80(p, 4, 0, 0);
        v = *(unsigned short *) (p + 0x98);
        func_ov002_02207e80(p, 6, 0, 0x50 - v);
        *(int *) (p + 0x94) = func_ov002_02207f60(p);
    }
}
