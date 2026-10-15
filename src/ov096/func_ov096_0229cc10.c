/* func_ov096_0229cc10 @ 0x0229cc10, 0x14 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229cbe0(void *s, int a);

typedef struct {
    char pad_00[0xbd];
    char flag;
} UnkStruct_0229cc10;

int func_ov096_0229cc10(UnkStruct_0229cc10 *s)
{
    s->flag = 0;
    return func_ov096_0229cbe0(s, 1);
}
