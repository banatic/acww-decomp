/* func_ov116_0229e5bc @ 0x0229e5bc, 0x2a bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov116_0229e50c(void);
extern int func_ov116_0229e354(int);
extern int func_ov116_0229e5e8(int);
extern int func_ov116_0229e34c(int);

int func_ov116_0229e5bc(int r0)
{
    int r4 = r0;
    if (func_ov116_0229e50c() != 0) {
        return 1;
    }
    func_ov116_0229e354(r4);
    func_ov116_0229e5e8(r4);
    func_ov116_0229e34c(r4);
    return 1;
}
