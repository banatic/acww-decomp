/* func_02090168 @ 0x02090168, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Func02090168Struct {
    char pad_00[0x94a];
    unsigned short unk_94A;
};

void func_02090168(struct Func02090168Struct *s, unsigned short value)
{
    s->unk_94A = value;
}
