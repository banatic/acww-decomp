/* func_ov004_0223b958 @ 0x0223b958, 0x120 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0223b958 {
    short x, y;
    UnkStruct_0223b958(short a, short b)
    {
        x = a;
        y = b;
    }
};

extern "C" void func_0204f818(int *px, int *py, int c);
extern const signed char data_ov004_02247ce0[];

extern "C" int func_ov004_0223b958(int *px, int *py, int c, int d, int i)
{
    static UnkStruct_0223b958 tbl[16] = {
        UnkStruct_0223b958(0, 1),  UnkStruct_0223b958(1, 1),   UnkStruct_0223b958(1, 1),   UnkStruct_0223b958(1, 0),
        UnkStruct_0223b958(1, 0),  UnkStruct_0223b958(1, -1),  UnkStruct_0223b958(1, -1),  UnkStruct_0223b958(0, -1),
        UnkStruct_0223b958(0, -1), UnkStruct_0223b958(-1, -1), UnkStruct_0223b958(-1, -1), UnkStruct_0223b958(-1, 0),
        UnkStruct_0223b958(-1, 0), UnkStruct_0223b958(-1, 1),  UnkStruct_0223b958(-1, 1),  UnkStruct_0223b958(0, 1)};
    int k;

    func_0204f818(px, py, c);
    if (i == 0) {
        return 1;
    }
    if (i < 4) {
        if (i != 0) {
            k = (((d >> 12) & 0xf) + data_ov004_02247ce0[i]) & 0xf;
            *px += tbl[k].x;
            *py += tbl[k].y;
        }
        return 1;
    }
    return 0;
}
