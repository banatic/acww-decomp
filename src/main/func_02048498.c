/* func_02048498 @ 0x02048498, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int unk_00;
    char pad_04[0x30];
    int unk_34;
    int unk_38;
} UnkStruct_02048498;
extern UnkStruct_02048498 data_021c79c4;
extern int func_0204851c(int a, int b, int c, int d);
extern void func_020484c8(int, int);

void func_02048498(int a, int b, int c, int d)
{
    int v1, v2;
    if (data_021c79c4.unk_00 != 0) {
        goto other;
    }
    v1 = data_021c79c4.unk_34;
    v2 = data_021c79c4.unk_38;
    if (v1 < 0 && v2 < 0) {
        func_0204851c(a, b, c, d);
    }
    return;
other:
    func_020484c8(a, b);
}
