/* func_ov100_0229e668 @ 0x0229e668, 0x84 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov002_02207e90(void *, int);
extern void func_ov100_0229c2b0(void *, int);
extern void func_02002708(int);
extern void func_ov002_02208090(void *, int);
extern void func_ov100_0229e218(void *);

void func_ov100_0229e668(void *arg)
{
    int cond;
    int zero;

    cond = func_ov002_02207f48(arg, 0);
    zero = 0;
    func_ov002_02207e80(arg, 6, zero, zero);
    *(int *) ((char *) arg + 0x28C4) = func_ov002_02207f60(arg);

    if (cond != 0) {
        func_ov100_0229e218(arg);
        func_ov002_02207f20(arg, 2, zero, 1, 0x30);
        func_ov002_02207e90(arg, 0x80);
        func_ov100_0229c2b0(arg, 0x80);
        func_02002708(4);
        func_ov002_02207e80(arg, 4, zero, zero);
        *(int *) ((char *) arg + 0x28C8) = func_ov002_02207f60(arg);
        func_ov002_02208090(arg, 3);
    }
}
