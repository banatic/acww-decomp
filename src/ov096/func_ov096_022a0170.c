/* func_ov096_022a0170 @ 0x022a0170, 0x1a bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_022a018c(int unused0);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov096_022a0170(int param)
{
    int r4 = param;
    if (func_ov096_022a018c(param) != 0) {
        func_ov002_02208098((void *) (r4), 0x1f);
    }
}
