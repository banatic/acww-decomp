/* func_020b682c @ 0x020b682c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *data_021f6948;

int func_020b682c(void)
{
    unsigned int *ptr;
    int result;

    result = 0;
    ptr = data_021f6948;
    if (ptr != 0) {
        result = *(int *) ((char *) ptr + 8);
    }
    return result;
}
