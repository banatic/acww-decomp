/* func_0209def4 @ 0x0209def4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209def4 {
    unsigned int unk_00;
    unsigned int unk_04;
};
extern unsigned char data_021dc754[];

void func_0209def4(unsigned char *out)
{
    struct UnkStruct_0209def4 *p = (struct UnkStruct_0209def4 *) data_021dc754;
    out[0] = (unsigned char) p->unk_04;
    out[1] = (unsigned char) p->unk_00;
}
