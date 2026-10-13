/* func_02084560 @ 0x02084560, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02084af0(void);
extern int func_02084630(int, int, int);
extern int func_02084598(int, int, int);

int func_02084560(int r5, int r4, int r6)
{
    int result;

    func_020984e8();
    result = func_02084af0();

    if (result != 0) {
        return func_02084630(r5, r4, r6);
    } else {
        return func_02084598(r5, r4, r6);
    }
}
