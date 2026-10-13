/* func_020953a4 @ 0x020953a4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);

void func_020953a4(int *param)
{
    int *result;
    int *ptr;

    result = (int *) func_02096718(4);
    if (result != 0) {
        ptr = (int *) param;
        *(int *) ((char *) result + 0x808) = *ptr;
    }
}
