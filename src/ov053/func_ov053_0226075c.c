/* func_ov053_0226075c @ 0x0226075c, 0x32 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099670(int);
extern unsigned int func_02088bc0(int);
extern int func_02099870(int);
extern int func_020950c0(int);

int func_ov053_0226075c(void *receiver)
{
    int first = func_020984e8();

    if (func_02088bc0(func_02099670(first)) >= 0x10) {
        if (func_020950c0(func_02099870(first)) == 0) {
            return 0x15;
        } else {
            return 0x16;
        }
    }
    return 0x3e;
}
