/* func_020819ac @ 0x020819ac, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7c];
    unsigned short flag;
} UnkStruct_020819ac;

void func_020819ac(UnkStruct_020819ac *s)
{
    s->flag |= 0x80;
}
