/* func_020b4d60 @ 0x020b4d60, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b4d60(int *param1, int param2);

int func_020b4d60(int *param1, int param2)
{
    int result;
    int *ptr;

    result = 1;
    ptr = (int *) ((char *) param1 + 0x3c);
    if (*ptr == param2) {
        result = 0;
    }
    return result;
}
