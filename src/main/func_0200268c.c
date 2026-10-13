/* func_0200268c @ 0x0200268c, 0x7a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(char *dst, char *src, int size);
void func_0200268c(char *dst, char *src, int width, int blocks)
{
    int src_off = 0;
    int col;
    int row;
    int block_off = 0;
    int p;
    int block = 0;
    int stride = width * 4;
    int block_size = width * 32;
    int col_init = src_off;
    int row_init = src_off;
    int q;
    while (block < blocks) {
        p = block_off;
        for (col = col_init; col < width; col++) {
            q = p;
            row = row_init;
            do {
                MI_CpuCopy8(dst + q, src + src_off, 4);
                src_off += 4;
                q += stride;
                row++;
            } while (row < 8);
            p += 4;
        }

        block_off += block_size;
        block++;
    }
}
