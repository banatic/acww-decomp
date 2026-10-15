/* func_ov100_0229dba0 @ 0x0229dba0, 0x30 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *ptr);
extern void func_ov100_0229d788(void *p, unsigned char b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov100_0229dba0(void *arg)
{
    if (func_ov002_02209f9c((char *) arg + 0x2274) != 0) {
        func_ov100_0229d788(arg, *((unsigned char *) ((char *) arg + 0x2921)));
        func_ov002_02208098((void *) (arg), 0xc);
    }
}
