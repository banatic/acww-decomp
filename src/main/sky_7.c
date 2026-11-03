/* sky_7: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bc110 @ 0x020bc110, 0xac bytes, Thumb
 * func_020bc078 @ 0x020bc078, 0x98 bytes, Thumb
 */

typedef struct {
    char pad_00[0x24];
    int unk_24;
    int unk_28;
} UnkStruct_020bc078;

extern int data_021f8ad4;
extern int data_021f8ad8;
extern void **data_020e6084[];
extern void func_020bbbf0(void *dst, void *src1, void *src2, void *arg);
extern unsigned char data_021f6cf0[];
extern UnkStruct_020bc078 data_021f8ab0;
extern unsigned short *data_020e6098[];
extern void func_020b68c8(unsigned int value);

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

void func_020bc078(unsigned int a0, unsigned int x, unsigned int y, unsigned int z)
{
    unsigned int f24 = data_021f8ab0.unk_24;
    unsigned int f28 = data_021f8ab0.unk_28;
    if (f28 != f24) {
        unsigned short *row;
        unsigned int v, w;
        row = data_020e6098[f24];
        v = ((0x1000 - a0) * row[y] + a0 * row[z]) << 4 >> 16;
        row = data_020e6098[f28];
        w = ((0x1000 - a0) * row[y] + a0 * row[z]) << 4 >> 16;
        func_020b68c8(((v * (0x1000 - x) + w * x) << 4) >> 16);
        return;
    }
    func_020b68c8(((0x1000 - a0) * data_020e6098[f24][y] + a0 * data_020e6098[f24][z]) << 4 >> 16);
}
