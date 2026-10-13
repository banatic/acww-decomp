/* func_02034714 @ 0x02034714, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02034714 {
    int arr[6][6][2];
    int unk_120;
    int unk_124;
    int unk_128;
    int unk_12C;
    char unk_130;
    short unk_132;
    short unk_134;
};

void func_02034714(struct UnkStruct_02034714 *d)
{
    int i;
    int j;
    d->unk_124 = 0;
    d->unk_128 = 0;
    d->unk_120 = 0;
    d->unk_132 = 0;
    d->unk_134 = 0;
    d->unk_12C = -1;
    d->unk_130 = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            d->arr[i][j][0] = 0;
            d->arr[i][j][1] = 0;
        }
    }
}
