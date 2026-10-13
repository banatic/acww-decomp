/* func_020bc110 @ 0x020bc110, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f8ad4;
extern int data_021f8ad8;
extern void **data_020e6084[];
extern void func_020bbbf0(void *dst, void *src1, void *src2, void *arg);

extern unsigned char data_021f6cf0[];

void func_020bc110(void *arg0, void *arg1, int arg2, int arg3)
{
    unsigned short *dst;
    int off;
    void **row;
    void *base;
    int i;
    int sx;
    int sy;
    unsigned short scratch[2];

    dst = (unsigned short *) data_021f6cf0;

    if (data_021f8ad8 != data_021f8ad4) {
        i = 0;
        sx = arg3 * 2;
        sy = arg2 * 2;
        for (; i < 4; i++) {
            row = data_020e6084[data_021f8ad4];
            off = i * 4;
            base = *(void **) ((unsigned char *) row + off);
            func_020bbbf0(scratch, (unsigned char *) base + sy, (unsigned char *) base + sx, arg0);
            row = data_020e6084[data_021f8ad8];
            base = *(void **) ((unsigned char *) row + off);
            func_020bbbf0(scratch + 1, (unsigned char *) base + sy, (unsigned char *) base + sx, arg0);
            func_020bbbf0(dst, scratch, scratch + 1, arg1);
            dst++;
        }
    } else {
        row = data_020e6084[data_021f8ad4];
        i = 0;
        sx = arg3 * 2;
        sy = arg2 * 2;
        for (; i < 4; i++) {
            base = row[i];
            func_020bbbf0(dst, (unsigned char *) base + sy, (unsigned char *) base + sx, arg0);
            dst++;
        }
    }
}
