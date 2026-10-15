/* func_ov094_0229b4c0 @ 0x0229b4c0, 0x30 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov094_0229c124[];
extern int func_020896b8(int, void *, int, int, int, int, int);

struct UnkStruct_0229b4c0 {
    char pad_00[0x20];
    int unk_20;
};

void func_ov094_0229b4c0(struct UnkStruct_0229b4c0 *ptr, int a, int b, int c)
{
    func_020896b8(1, data_ov094_0229c124, a - 8, b - 8, -1, ptr->unk_20, c);
}
