/* func_ov098_022a2884 @ 0x022a2884, 0x28 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02219c80(void);
extern void func_ov002_02208098(int, int);
extern void func_ov002_0220b764(int);

void func_ov098_022a2884(int r0)
{
    int r4 = r0;
    if (func_ov003_02219c80() != 0) {
        func_ov002_02208098(r4, 0x37);
        func_ov002_0220b764(r4 + 0x2958);
    }
}
