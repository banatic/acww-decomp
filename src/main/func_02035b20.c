/* func_02035b20 @ 0x02035b20, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da2b4;

struct UnkStruct_02035b20 {
    char *unk_00;
    unsigned int unk_04;
    unsigned short unk_08;
    unsigned char unk_0A;
};

void func_02035b20(struct UnkStruct_02035b20 *this, unsigned int value)
{
    this->unk_00 = &data_020da2b4;
    this->unk_04 = value;
    this->unk_08 = 0xffff;
    this->unk_0A = 0;
}
