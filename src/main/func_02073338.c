/* func_02073338 @ 0x02073338, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x118];
    int member;
} UnkStruct_02073338;

void func_02073338(UnkStruct_02073338 *s, int val)
{
    s->member = val;
}
