/* func_0207e1c4 @ 0x0207e1c4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02099870(void);
extern int func_02094ffc(void);
extern int func_02098880(char *ptr);
extern char data_021dc7bc[];

int func_0207e1c4(void)
{
    func_02099870();
    if (func_02094ffc() == 0 && func_02098880(data_021dc7bc) == 4) {
        return 1;
    }
    return 0;
}
