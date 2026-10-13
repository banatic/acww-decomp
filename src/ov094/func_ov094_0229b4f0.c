/* func_ov094_0229b4f0 @ 0x0229b4f0, 0x30 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_020896b8(int, int *, int, int, int, int, int);
extern int data_ov094_0229c11c[];

typedef struct UnkStruct_0229b4f0 {
    char pad_00[0x20];
    int unk_20;
} UnkStruct_0229b4f0;

void func_ov094_0229b4f0(UnkStruct_0229b4f0 *obj, int a, int b, int c, int d)
{
    func_020896b8(1, data_ov094_0229c11c, a - 8, b - 8, c, obj->unk_20, d);
}
