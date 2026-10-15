/* func_020415d0 @ 0x020415d0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e980(void);
extern void func_020413f8(int);

void func_020415d0(void *receiver)
{
    int result;
    result = func_0206e980();
    if (result == 0) {
        func_020413f8(3);
    }
}
