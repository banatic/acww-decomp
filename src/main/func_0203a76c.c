/* func_0203a76c @ 0x0203a76c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021f3a68[15];

void func_0203a76c(unsigned short value)
{
    unsigned short *p = data_021f3a68;
    int found = 15;
    int exit_val = found;
    int i;

    for (i = 0; i < 15; i++) {
        if (p[i] == 0xfff1) {
            found = i;
            i = exit_val;
        }
    }

    if (found == 15) {
        for (found = 0; found < 14; found++) {
            p[found] = p[found + 1];
        }
        found = 14;
    }

    p[found] = value;
}
