/* func_0206ffe8 @ 0x0206ffe8, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0207004c(int);
extern int func_0206fcb0(void *);

void *func_0206ffe8(void *arg)
{
    void *result;
    void *temp;

    result = func_0207004c(0xc);
    if (result != 0) {
        temp = arg;
        func_0206fcb0(temp);
    }
    return result;
}
