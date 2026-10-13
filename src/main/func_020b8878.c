/* func_020b8878 @ 0x020b8878, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b8878(void *ptr)
{
    int result;
    int val1;
    int val2;

    val1 = *(int *) ((char *) ptr + 0x100);
    if (val1 != 0) {
        result = 1;
    } else {
        result = 0;
    }

    val2 = *(int *) ((char *) ptr + 0x108);
    if (val2 == 0) {
        result = 0;
    }

    return result;
}
