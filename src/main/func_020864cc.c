/* func_020864cc @ 0x020864cc, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020864cc(unsigned int x)
{
    int count;
    int i;

    count = 0;
    if (x != 0) {
        i = count;
        do {
            if ((x >> i) & 1) {
                count++;
            }
            i++;
        } while (i < 32);
    }
    return count;
}
