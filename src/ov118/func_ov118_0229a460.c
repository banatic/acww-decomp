/* func_ov118_0229a460 @ 0x0229a460, 0x12 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a460 {
    char pad_00[0x9c];
    unsigned short unk_9C;
};

int func_ov118_0229a460(struct UnkStruct_0229a460 *s, unsigned short mask)
{
    int t = s->unk_9C & mask;
    if (t == 0) {
        return 0;
    } else {
        return 1;
    }
}
