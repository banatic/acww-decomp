/* func_ov048_022615dc @ 0x022615dc, 0x2c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209fe40(void);
extern void func_ov048_022616b8(int, int);

void func_ov048_022615dc(int param)
{
    int *p;
    int val;

    if (func_0209fe40() != 0) {
        p = (int *) (param + 0xb4);
        val = *p + 1;
        func_ov048_022616b8(param, val);
    } else {
        p = (int *) (param + 0xb4);
        val = *p + 2;
        func_ov048_022616b8(param, val);
    }
}
