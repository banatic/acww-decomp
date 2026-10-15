/* func_ov096_022a062c @ 0x022a062c, 0x28 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov096_0229dc28(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov096_022a062c(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x2500)) {
        func_ov096_0229dc28(arg0);
        func_ov002_02208098((void *) (arg0), 0xa);
    }
}
