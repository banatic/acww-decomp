/* func_ov104_0229c9c4 @ 0x0229c9c4, 0x38 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(const void *);
extern int func_02065e9c(const void *);

int func_ov104_0229c9c4(int unused, const char *ptr)
{
    int i;
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(ptr) == 1 && func_02065e9c(ptr) != 0) {
            return 1;
        }
        ptr += 0x100;
    }
    return 0;
}
