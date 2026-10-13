/* func_0206fdd4 @ 0x0206fdd4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206fdd4 {
    unsigned int w;
    unsigned int m;
};

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
