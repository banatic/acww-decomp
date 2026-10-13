/* func_02068340 @ 0x02068340, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02068340 {
    unsigned char pad_00[0x14a8];
    unsigned int unk_14A8;
};

extern void func_02066854(unsigned int val, struct UnkStruct_02068340 *s);

void func_02068340(struct UnkStruct_02068340 *s, unsigned int val)
{
    s->unk_14A8 = val;
    func_02066854(val, s);
}
