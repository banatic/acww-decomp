/* func_020ae270 @ 0x020ae270, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_02094ffc(void *);
extern int func_020ae3b8(void *);
extern int func_020ae494(signed char *);
extern int func_0209871c(void *, int);
extern void func_020ae514(int, int);

extern unsigned char data_021dc7bc[];
extern unsigned char data_021f3b30[];

int func_020ae270(void)
{
    int tested_value0;
    if ((tested_value0 = (int) (func_020984e8())) != 0) {
        int v = func_02099870(tested_value0);
        if (func_02094ffc((void *) v) == 1) {
            return func_020ae494((signed char *) func_020ae3b8((void *) data_021f3b30));
        } else {
            v = (unsigned char) (func_0209871c((void *) data_021dc7bc, v) & 3);
            func_020ae514(func_020ae3b8((void *) data_021f3b30), v);
            return 1;
        }
    }
    return 0;
}
