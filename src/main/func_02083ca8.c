/* func_02083ca8 @ 0x02083ca8, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1b70;

struct UnkStruct_02083ca8 {
    unsigned int unk_00;
    unsigned int unk_04;
};

void func_02083ca8(struct UnkStruct_02083ca8 *r0, unsigned int r1)
{
    r0->unk_00 = (unsigned int) &data_020e1b70;
    r0->unk_04 = r1;
}
