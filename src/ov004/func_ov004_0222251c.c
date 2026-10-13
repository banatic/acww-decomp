/* func_ov004_0222251c @ 0x0222251c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_021e5a2c;
extern void *func_0207b410(void *);
extern int func_0209a6ec(void *);
extern void func_02015e40(void *, int, int);
void func_ov004_0222251c(void *self)
{
    void *o;
    o = func_0207b410(&data_021e5a2c);
    if (o != 0) {
        if (func_0209a6ec(o) != 0) {
            func_02015e40(self, func_0209a6ec(o), 0);
        }
    }
}
