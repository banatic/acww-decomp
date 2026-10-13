/* func_0206fd60 @ 0x0206fd60, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// Unused.

void func_0206fd60(unsigned short *base, int start_j, int start_i, int end_j, int end_i, unsigned int match,
                   unsigned int replace)
{
    int i, j, idx;
    unsigned int match_shift;
    unsigned int replace_shift;
    unsigned int masked;
    unsigned int new_val;
    unsigned short val;
    unsigned short *p;

    match_shift = (match << 28) >> 16;
    replace_shift = (replace << 28) >> 16;

    for (i = start_i; i <= end_i; i++) {
        j = start_j;
        idx = i * 32 + j;
        for (; j <= end_j; j++) {
            p = &base[idx];
            val = *p;
            masked = val & 0xF000;
            if (match_shift == masked) {
                new_val = replace_shift | (val & 0x0FFF);
                *p = (unsigned short) new_val;
            }
            idx++;
        }
    }
}
