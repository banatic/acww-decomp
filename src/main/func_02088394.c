/* func_02088394 @ 0x02088394, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099688(void);
extern int func_020882c4(void);
extern int func_020882dc(int);
extern int func_020e8b0c(int, int, int);

int func_02088394(void)
{
    if (func_020984e8() != 0) {
        int tmp = func_02099688();
        if (func_020882c4() == 1) {
            int arg = func_020882dc(tmp);
            if (func_020e8b0c(arg, 1, 7) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
