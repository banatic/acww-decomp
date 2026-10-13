/* func_02015564 @ 0x02015564, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015564(void *param);

int func_02015564(void *param)
{
    int result;
    unsigned int *ptr;
    int val;

    result = 0;
    ptr = *(unsigned int **) ((char *) param + 0x40);
    if (ptr != 0) {
        val = *(int *) ((char *) ptr + 4);
        if (val == 5) {
            result = 1;
        }
    }
    return result;
}
