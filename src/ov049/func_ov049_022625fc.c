/* func_ov049_022625fc @ 0x022625fc, 0x30 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_020b5e10(void);
extern void func_020b6098(int, int);
extern void func_ov049_02262a94(void *, int);

int func_ov049_022625fc(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_020b6098(func_020b5e10(), 0);
        func_ov049_02262a94(self, 6);
    }
    return 1;
}
