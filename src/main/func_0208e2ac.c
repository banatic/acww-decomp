/* func_0208e2ac @ 0x0208e2ac, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xC];
    int unk_0C;
    int unk_10;
} UnkStruct_0208e2ac;

extern int data_020d0ac8[];
extern void func_0208e144(UnkStruct_0208e2ac *a);

void func_0208e2ac(UnkStruct_0208e2ac *a, int index)
{
    int val;

    a->unk_0C = index;
    val = data_020d0ac8[index];
    a->unk_10 = val;
    func_0208e144(a);
}
