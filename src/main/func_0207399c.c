/* func_0207399c @ 0x0207399c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int x);

typedef struct {
    char pad_00[0x58];
    int counter[1];
} UnkStruct_0207399c;

void func_0207399c(UnkStruct_0207399c *s, int param)
{
    s->counter[func_02077b58(param)]++;
}
