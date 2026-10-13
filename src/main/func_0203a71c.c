/* func_0203a71c @ 0x0203a71c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021f3a68[];

int func_0203a71c(void)
{
    int count;
    unsigned short *p;
    int i;
    count = 0;
    p = data_021f3a68;
    i = 0;
    do {
        if (p[i] != 0xfff1) {
            count++;
        }
        i++;
    } while (i < 15);
    return count;
}
