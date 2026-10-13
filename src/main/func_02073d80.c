/* func_02073d80 @ 0x02073d80, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02073d80 {
    unsigned int pad_00;
    unsigned short unk_04;
};

short func_02073d80(struct UnkStruct_02073d80 *s)
{
    return s->unk_04 & 0x7fff;
}
