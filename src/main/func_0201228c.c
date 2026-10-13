/* func_0201228c @ 0x0201228c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201228c {
    unsigned short unk_00;
};

extern void func_020122ac(struct UnkStruct_0201228c *a, struct UnkStruct_0201228c *b, int c, int d);

void func_0201228c(struct UnkStruct_0201228c *a, int b, int c)
{
    if (a->unk_00 != 0xfff1) {
        func_020122ac(a, a, b, c);
    }
}
