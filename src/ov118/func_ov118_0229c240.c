/* func_ov118_0229c240 @ 0x0229c240, 0x60 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int v);
extern void func_ov002_022080a0(void *p, int v);
extern int func_0206fe60(void);
extern void func_ov118_0229b8b0(void *p);
extern void func_ov118_0229b868(void *p);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

void func_ov118_0229c240(char *p)
{
    unsigned short v;

    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        if (func_0206fe60()) {
            func_ov118_0229b8b0(p);
        } else {
            func_ov118_0229b868(p);
        }
    }
    func_ov002_02207e80(p, 4, 0, 0);
    v = *(unsigned short *) (p + 0x98);
    func_ov002_02207e80(p, 6, 0, 0x50 - v);
    *(int *) (p + 0x94) = func_ov002_02207f60(p);
}
