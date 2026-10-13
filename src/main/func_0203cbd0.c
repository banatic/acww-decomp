/* func_0203cbd0 @ 0x0203cbd0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(int);
extern int func_020996ac(int);
extern int OS_UnlockByWord_IrqAndFiq(int, int, int);

int func_0203cbd0(int param)
{
    int result = func_020984e8(param);
    if (result != 0) {
        return OS_UnlockByWord_IrqAndFiq(func_020996ac(result), param, 1);
    } else {
        return 0;
    }
}
