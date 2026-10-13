/* func_0204de14 @ 0x0204de14, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060da8(int arg);
extern int func_02037e88(int arg1, int arg2);

extern unsigned char data_021ebcd4[];

int func_0204de14(int *p)
{
    int y;
    y = func_02060da8((unsigned int) data_021ebcd4);
    if (*p != 0) {
        return func_02037e88(*p, y);
    }
    return *p;
}
