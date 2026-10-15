/* func_02037d80 @ 0x02037d80, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02037d9c(int *p);

int func_02037d80(unsigned int param1, unsigned int param2)
{
    unsigned int result;
    unsigned int temp;

    temp = func_02037d9c((int *) param1);
    result = param2 & temp;
    if (param2 == result) {
        return 1;
    } else {
        return 0;
    }
}
