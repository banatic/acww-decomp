/* func_ov003_02234984 @ 0x02234984, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x244];
    short t;
} UnkStruct_02234984;
int func_ov003_02234984(UnkStruct_02234984 *s)
{
    if (s->t > 0) {
        s->t--;
    } else {
        return 1;
    }
    return 0;
}
