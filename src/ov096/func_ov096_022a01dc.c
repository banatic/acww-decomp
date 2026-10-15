/* func_ov096_022a01dc @ 0x022a01dc, 0x3c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov096_0229dc7c(int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_02208e28(int);

void func_ov096_022a01dc(int r0)
{
    if (func_ov002_02208e28(r0 + 0x2564) != 0) {
        if (func_0206fe54() != 0) {
            func_ov096_0229dc7c(r0);
            func_ov002_02208098((void *) (r0), 0xd);
        } else {
            func_ov002_02208098((void *) (r0), 4);
        }
    }
}
