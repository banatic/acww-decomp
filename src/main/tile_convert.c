/* tile_convert: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200268c @ 0x0200268c, 0x7a bytes, Thumb
 * func_02002628 @ 0x02002628, 0x64 bytes, Thumb
 * func_020025c4 @ 0x020025c4, 0x64 bytes, Thumb
 * func_0200255c @ 0x0200255c, 0x68 bytes, Thumb
 * func_020024f0 @ 0x020024f0, 0x6c bytes, Thumb
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

void func_02002628(int *src, int *dst, int n, int innerCount, int outerCount)
{
    int idx = 0;
    int outer;
    int k;
    int rowbase = n * 8;

    for (outer = 0; outer < outerCount; outer++) {
        int j;
        int pos = rowbase;
        for (j = 0; j < 8; j++) {
            int col = pos;
            for (k = 0; k < innerCount; k++) {
                dst[idx] = src[col];
                idx++;
                col += 8;
            }
            pos++;
        }
        rowbase += 0x100;
    }
}

void func_020025c4(int *src, int *dst, int n, int innerCount, int outerCount)
{
    int idx = 0;
    int outer;
    int k;
    int rowbase = n * 8;

    for (outer = 0; outer < outerCount; outer++) {
        int j;
        int pos = rowbase;
        for (j = 0; j < 8; j++) {
            int col = pos;
            for (k = 0; k < innerCount; k++) {
                dst[col] = src[idx];
                idx++;
                col += 8;
            }
            pos++;
        }
        rowbase += 0x100;
    }
}

void func_0200255c(int *src, int *dst, int n, int m)
{
    int outer;
    int k;
    int idx = 0;
    int rowbase = 0;

    for (outer = 0; outer < m; outer++) {
        int j;
        int pos = rowbase;
        for (j = 0; j < 8; j++) {
            int col = pos;
            for (k = 0; k < n; k++) {
                dst[col] = src[idx];
                idx++;
                col += 8;
            }
            pos++;
        }
        rowbase += n * 8;
    }
}

void func_020024f0(int *src, int *dst, int n, int m)
{
    int outer;
    int k;
    int idx = 0;
    int rowbase = 0;

    for (outer = 0; outer < m; outer++) {
        int j;
        int pos = rowbase;
        for (j = 0; j < 8; j++) {
            int col = pos;
            for (k = 0; k < n; k++) {
                dst[idx] = src[col];
                idx++;
                col += 8;
            }
            pos++;
        }
        rowbase += n * 8;
    }
}
