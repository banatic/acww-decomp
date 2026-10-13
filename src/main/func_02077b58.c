/* func_02077b58 @ 0x02077b58, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ec260(void);

int func_02077b58(int a)
{
    int b = func_020ec260();
    if (a >= b) {
        a = a - 1;
    }
    return a;
}
