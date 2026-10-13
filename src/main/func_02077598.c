/* func_02077598 @ 0x02077598, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void (*data_020cd1dc[])(int);
extern int data_020ccf94;
extern int func_020738bc(int a, int b);

void func_02077598(int p0)
{
    void (*f)(int) = data_020cd1dc[p0];
    if (f != 0) {
        f(func_020738bc(data_020ccf94, p0));
    }
}
