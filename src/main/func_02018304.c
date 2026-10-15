/* func_02018304 @ 0x02018304, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(void *ptr, int);
extern int func_02057c20(void *ptr);
extern int func_02057d0c(int a, void *ptr);

void func_02018304(void *arg0, void *arg1)
{
    int result;
    char *ptr;

    result = func_020164cc((char *) arg1 + 0x334, (int) arg1);
    if (result != 0) {
        result = func_02057c20(arg1);
        if (result != 0) {
            result = func_02057d0c(3, arg1);
            if (result != 0) {
                ptr = (char *) arg0 + 0x98;
                *ptr = 3;
            }
        }
    }
}
