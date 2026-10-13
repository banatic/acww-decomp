/* func_02017c70 @ 0x02017c70, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(void *ptr);
extern int func_02057c20(void *ptr);
extern int func_02057d0c(int a, void *ptr);

void func_02017c70(void *param0, void *param1)
{
    int result;
    unsigned char *ptr;

    result = func_020164cc((char *) param1 + 0x334);
    if (result != 0) {
        result = func_02057c20(param1);
        if (result != 0) {
            result = func_02057d0c(3, param1);
            if (result != 0) {
                ptr = (unsigned char *) param0 + 0x98;
                *ptr = 0x10;
            }
        }
    }
}
