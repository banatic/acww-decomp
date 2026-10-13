/* func_ov048_02261578 @ 0x02261578, 0x2c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ff54(void);
extern void func_ov048_022616b8(int, int);

void func_ov048_02261578(int arg0)
{
    int r4;
    int r1;

    r4 = arg0;
    if (func_0209ff54() != 0) {
        r1 = *(int *) (r4 + 0xb4);
        func_ov048_022616b8(r4, r1 + 1);
    } else {
        r1 = *(int *) (r4 + 0xb4);
        func_ov048_022616b8(r4, r1 + 2);
    }
}
