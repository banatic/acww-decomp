/* func_ov003_0221a484 @ 0x0221a484, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(unsigned short *arg);
extern int func_0204bc64(unsigned short *arg);
extern int func_0204bd08(unsigned short *arg);
extern void func_0203a76c(unsigned short value);

int func_ov003_0221a484(unsigned short *arg)
{
    int ret;
    if (func_0204bcdc(arg) != 0) {
        unsigned short local = 0xfff1;
        ret = (func_0204bc64(arg) == func_0204bc64(&local)) ? 1 : 0;
    } else {
        ret = (*arg == 0xfff1) ? 1 : 0;
    }
    if (ret == 0 && (func_0204bd08(arg) != 0 || func_0204bcdc(arg) != 0)) {
        func_0203a76c(*arg);
        return 1;
    }
    return 0;
}
