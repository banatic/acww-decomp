/* func_ov086_02278ee4 @ 0x02278ee4, 0x2c bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov086_02278f80(void *, int);

int func_ov086_02278ee4(void *arg0)
{
    if (func_02014868((char *) arg0 + 0x618) == 0) {
        func_0203e020(arg0);
        func_ov086_02278f80(arg0, 2);
    }
    return 1;
}
