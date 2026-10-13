/* func_0205d8f4 @ 0x0205d8f4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0205d8f4 {
    char pad_00[0x24];
    short data[1][9];
};

void func_0205d8f4(struct UnkStruct_0205d8f4 *p, int col, int row, short value)
{
    p->data[row][col] = value;
}
