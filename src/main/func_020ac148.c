/* func_020ac148 @ 0x020ac148, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x14];
    int count;
    short unk_18;
    short unk_1A;
    short unk_1C;
    short unk_1E;
} UnkStruct_020ac148;

int func_020ac148(UnkStruct_020ac148 *self, int arg1, int arg2)
{
    int result;
    int i;
    int start, end;
    int bstart, bend;

    i = 0;
    result = ~i;
    start = 0x88 - self->unk_18;
    end = start + self->count * 8;
    if (arg1 >= start && arg1 < end) {
        bstart = self->unk_1C + 0x50 - self->unk_1A;
        for (; i < self->unk_1E; i++) {
            bend = bstart + 0x10;
            if (arg2 >= bstart && arg2 < bend) {
                result = i;
                break;
            }
            bstart = bend;
        }
    }
    return result;
}
