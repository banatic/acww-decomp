/* func_02034ee4 @ 0x02034ee4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02034ee4(char *base, unsigned short key)
{
    unsigned short *id;
    int result;
    int i;
    int count;

    result = -1;
    count = *(int *) (base + 0x1c0);
    for (i = 0; i < count; i++) {
        id = (unsigned short *) (base + i * 0x1c + 4);
        if (*id == key) {
            result = i;
            break;
        }
    }
    return result;
}
