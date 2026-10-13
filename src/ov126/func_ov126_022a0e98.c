/* func_ov126_022a0e98 @ 0x022a0e98, 0x2c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov126_022a1b4c(int);
extern int func_ov002_02208098(int, unsigned char);
extern int func_ov002_02209f64(int);

void func_ov126_022a0e98(int r0)
{
    if (func_ov002_02209f64(r0 + 0x3f90) == 0) {
        func_ov002_02208098(r0, *(unsigned char *) (r0 + 0xae));
        func_ov126_022a1b4c(r0);
    }
}
