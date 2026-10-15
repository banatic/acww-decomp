/* func_02084af0 @ 0x02084af0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099020(int arg1, int arg2);

int func_02084af0(void)
{
    int result = func_020984e8();
    return result && func_02099020(result, 1);
}
