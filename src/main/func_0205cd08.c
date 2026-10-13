/* func_0205cd08 @ 0x0205cd08, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0205cd08(unsigned short *array, int target)
{
    int i = 0;
    int max = 0x19;

    if (target < 0x137) {
        max = 9;
    } else {
        i = 9;
    }

    while (i < max) {
        unsigned short val = *(unsigned short *) ((char *) array + i * 2 + 100);
        if (val == target) {
            return i;
        }
        i++;
    }

    return 0x19;
}
