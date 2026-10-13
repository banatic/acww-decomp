/* func_020ae470 @ 0x020ae470, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ae458(void *param, unsigned int index);

int func_020ae470(void *param)
{
    unsigned int count = 0;
    unsigned int i = count;

    do {
        if (func_020ae458(param, i) == 0) {
            count++;
        }
        i++;
    } while (i < 32);

    return count;
}
