/* func_0204f7e0 @ 0x0204f7e0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0204f7e0 {
    int pad_00;
    int y;
};

struct UnkStruct_0204f7e0_2 {
    int x;
    int y;
    int z;
};

void func_0204f794(struct UnkStruct_0204f7e0 *a, int x, int z);

void func_0204f7e0(struct UnkStruct_0204f7e0 *a, struct UnkStruct_0204f7e0_2 *b)
{
    func_0204f794(a, b->x >> 13, b->z >> 13);
    a->y = b->y;
}
