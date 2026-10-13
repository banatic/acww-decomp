/* func_02031a48 @ 0x02031a48, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int, int);

int func_02031a48(int a, int b)
{
    if (func_01ffcb2c(a, b) == 30 && func_01ffcb2c(a, b + 1) == 8) {
        return 1;
    }
    return 0;
}
