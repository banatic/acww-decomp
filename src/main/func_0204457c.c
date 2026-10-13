/* func_0204457c @ 0x0204457c, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020445c0(unsigned short *out, void *arg3, unsigned short val);
extern int func_0204482c(void *arg1);
extern void func_02044750(unsigned short *out, unsigned char *flag, unsigned short val);

void func_0204457c(void *arg1, unsigned short *out, void *arg3, unsigned char *flag, unsigned short val)
{
    *out = val;
    *flag = 1;
    if (func_020445c0(out, arg3, val)) {
        *flag = 0;
        return;
    }
    if (func_0204482c(arg1)) {
        func_02044750(out, flag, val);
    }
}
