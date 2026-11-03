/* screen_map: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206fe28 @ 0x0206fe28, 0x10 bytes, Thumb
 * func_0206fdd4 @ 0x0206fdd4, 0x54 bytes, Thumb
 * func_0206fd60 @ 0x0206fd60, 0x74 bytes, Thumb
 */

struct UnkStruct_0206fdd4 {
    unsigned int w;
    unsigned int m;
};

int func_0206fe28(int n)
{
    return ((n & 0xF) << 1) + ((n >> 4) << 6);
}

void func_0206fdd4(unsigned short *buf, int start_col, int start_row, int end_col, int end_row, unsigned int v)
{
    struct UnkStruct_0206fdd4 t;
    unsigned int mask;
    int row;
    int col;
    int idx;

    mask = (v << 28) >> 16;
    row = start_row;
    while (row <= end_row) {
        col = start_col;
        idx = col + (row << 5);
        while (col <= end_col) {
            t.w = buf[idx];
            t.w &= 0xFFF;
            t.m = mask;
            t.m |= t.w;
            buf[idx] = (unsigned short) t.m;
            idx++;
            col++;
        }
        row++;
    }
}

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
