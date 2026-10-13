/* func_0209bd04 @ 0x0209bd04, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd10(unsigned char);

struct UnkStruct_0209bd04 {
    char pad_00[0xa];
    unsigned char unk_0A;
};

void func_0209bd04(struct UnkStruct_0209bd04 *self)
{
    func_0209bd10(self->unk_0A);
}
