/* func_020bc078 @ 0x020bc078, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    int unk_24;
    int unk_28;
} UnkStruct_020bc078;

extern UnkStruct_020bc078 data_021f8ab0;
extern unsigned short *data_020e6098[];
extern int func_020b68c8(int);

unsigned int func_020bc078(unsigned int a0, unsigned int x, unsigned int y, unsigned int z)
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
        return func_020b68c8(((v * (0x1000 - x) + w * x) << 4) >> 16);
    }
    return func_020b68c8(((0x1000 - a0) * data_020e6098[f24][y] + a0 * data_020e6098[f24][z]) << 4 >> 16);
}
