/* func_0203a694 @ 0x0203a694, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021f3a86[];
extern int func_0204c438(unsigned short *a, unsigned short *b);

int func_0203a694(unsigned int idx, unsigned short value)
{
    unsigned short local[2];

    if (idx >= 15) {
    } else {
        local[0] = value;
        local[1] = 0xfff1;
        if (func_0204c438(local, &local[1])) {
            data_021f3a86[idx] = local[1];
        }
        return 1;
    }
    return 0;
}
