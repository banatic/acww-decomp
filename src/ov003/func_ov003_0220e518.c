/* func_ov003_0220e518 @ 0x0220e518, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0220e5c4(void *, int, int, int);

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x490];
    short unk_C84;
} UnkStruct_0220e518;

void func_ov003_0220e518(UnkStruct_0220e518 *a, int b)
{
    int v = a->unk_7F0;
    if (v == 0x73) {
    } else if (v == 0x74) {
        a->unk_C84 = (short) b;
    } else {
        func_ov003_0220e5c4(a, -1, 6, b);
    }
}
