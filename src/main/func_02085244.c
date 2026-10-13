/* func_02085244 @ 0x02085244, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned char flag;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char pad_03[27];
};
extern struct Entry data_021d232c[];

int func_02085244(unsigned short *data, unsigned char a, unsigned char b)
{
    unsigned int index = *data & 0xFFF;
    if (index < 38) {
        struct Entry *e = &data_021d232c[index];
        e->flag = 1;
        e->unk_01 = a;
        e->unk_02 = b;
        return 1;
    }
    return 0;
}
