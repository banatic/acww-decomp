/* func_020960f8 @ 0x020960f8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(void *param1);

int func_020960f8(void *param1, void *param2)
{
    void *r4;
    void *r0;
    int result;

    r4 = param1;
    r0 = param2;
    result = func_02096718(r0);
    if (result != 0) {
        if (*(int *) ((char *) result + 0x7f0) == (int) r4) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
