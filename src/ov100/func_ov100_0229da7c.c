/* func_ov100_0229da7c @ 0x0229da7c, 0x54 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *p);
extern void func_ov002_02208098(void *p, unsigned char c);
extern int func_ov002_02209f9c(void *p);
extern int func_ov100_0229c2c0(void *p, int x);
extern int func_ov100_0229c2a0(void *p, int x);
extern void func_ov094_022999c0(int x);
extern void func_ov100_0229ce24(void *p);

void func_ov100_0229da7c(unsigned char *param)
{
    if (func_0208e484(param + 0x2274) != 0) {
        func_ov002_02208098(param, param[0x2924]);
    }
    if (func_ov002_02209f9c(param + 0x2274) != 0) {
        if (func_ov100_0229c2c0(param, 0x40) != 0) {
            func_ov094_022999c0(func_ov100_0229c2a0(param, 0x40));
        }
        func_ov100_0229ce24(param);
    }
}
