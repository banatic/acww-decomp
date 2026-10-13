/* func_ov002_02207eb4 @ 0x02207eb4, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208458(void *, int, int, int);

struct UnkStruct_02207eb4 {
    char pad_00[0x70];
    int value;
};

void func_ov002_02207eb4(struct UnkStruct_02207eb4 *a, int b, int c)
{
    if (b == 0) {
        b = 4;
    }
    func_ov002_02208458(&a->value, b, c, 0x30);
}
