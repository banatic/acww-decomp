/* func_02036b6c @ 0x02036b6c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020356c4(unsigned short, unsigned short, unsigned short, unsigned short);
typedef struct {
    char pad_00[0xc];
    unsigned short unk_0C;
} UnkStruct_02036b6c;
void func_02036b6c(UnkStruct_02036b6c *p, unsigned short val)
{
    func_020356c4(0x21, val, 0x7f, 0);
    p->unk_0C = val;
}
