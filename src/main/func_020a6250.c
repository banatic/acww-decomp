/* func_020a6250 @ 0x020a6250, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a627c(int *);
extern int func_020a7330(int);
extern int func_020b65c4(void);
extern void func_020a6280(int, int);

void func_020a6250(int arg0)
{
    int tested_value0;
    int val;
    int val2;

    if ((tested_value0 = (int) (func_020a627c((int *) arg0))) < 4) {
        val = func_020a7330(tested_value0);
        val2 = func_020b65c4();
        if (val == val2) {
            func_020a6280(arg0, 4);
        }
    }
    return;
}
