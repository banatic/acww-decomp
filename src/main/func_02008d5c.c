/* func_02008d5c @ 0x02008d5c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *, unsigned int, unsigned int, unsigned short);
extern int func_020912d4(int, void *, int, int);
extern int func_0200f328(void *, int);
extern void func_02008db8(void *, int);

struct UnkStruct_02008d5c {
    char pad_00[0xc];
    short unk_0C;
};

struct UnkStruct_02008d5c_2 {
    char pad_00[0x6e0];
    char unk_6E0[0xf4];
    short unk_7D4;
    char pad_7D6[0x11a];
    char unk_8F0[1];
};

void func_02008d5c(struct UnkStruct_02008d5c_2 *a, struct UnkStruct_02008d5c *b, int previous)
{
    short val = b->unk_0C;
    func_020109a0(a, 0x70, 3, 0);
    func_020912d4(0x43, a->unk_6E0, 0, 0);
    func_0200f328(a, 0x86);
    a->unk_7D4 = val;
    func_02008db8(a->unk_8F0, val);
}
