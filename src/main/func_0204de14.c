/* func_0204de14 @ 0x0204de14, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060da8(int arg, int);
extern void func_02037e88(int *object, int value);

extern unsigned char data_021ebcd4[];

void func_0204de14(int *p, int column)
{
    int value = func_02060da8((int) data_021ebcd4, column);
    int *object = (int *) *p;
    if (object != 0) {
        func_02037e88(object, value);
    }
}
