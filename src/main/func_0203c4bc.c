/* func_0203c4bc @ 0x0203c4bc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0203c4bc(void *ptr)
{
    int sum;
    sum = *(int *) ((char *) ptr + 0xC4) + *(int *) ((char *) ptr + 0xB4);
    if (sum < 0) {
        return 0;
    }
    return sum;
}
