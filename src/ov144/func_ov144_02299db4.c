/* func_ov144_02299db4 @ 0x02299db4, 0x40 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299db4 {
    char pad_00[0xB6];
    short unk_B6;
};
extern void func_0206fdd4(void *a, int b, int c, int d, int e, int f);

void func_ov144_02299db4(struct UnkStruct_02299db4 *a, int b, int c)
{
    int diff;
    int idx;
    if (b == -1) {
        return;
    }
    diff = b - a->unk_B6;
    if (diff < 0) {
        return;
    }
    if (diff >= 9) {
        return;
    }
    idx = b & 0xF;
    func_0206fdd4((char *) a + 0x110a, 0, idx * 2, 0x1f, idx * 2 + 1, c);
}
