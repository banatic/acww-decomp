/* func_ov094_0229a668 @ 0x0229a668, 0x34 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_020896b8(int, const void *, int, int, int, int, int);
extern const int data_ov094_0229bfa8[];

struct UnkStruct_0229a668 {
    char pad_00[0xa50];
    int unk_A50;
};

int func_ov094_0229a668(struct UnkStruct_0229a668 *obj, int x, int y)
{
    return func_020896b8(1, data_ov094_0229bfa8, x - 8, y - 8, -1, obj->unk_A50, 0);
}
