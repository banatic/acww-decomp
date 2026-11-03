/* town_item_lists_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203a76c @ 0x0203a76c, 0x4c bytes, Thumb
 * func_0203a744 @ 0x0203a744, 0x28 bytes, Thumb
 * func_0203a71c @ 0x0203a71c, 0x28 bytes, Thumb
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

int func_0203a744(void)
{
    int i;
    const unsigned short *table = ((const unsigned short *) data_021f3a68);

    for (i = 0; i < 15; i++) {
        if (table[i] != 0xfff1) {
            return 1;
        }
    }
    return 0;
}

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
