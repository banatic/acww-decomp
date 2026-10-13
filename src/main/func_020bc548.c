/* func_020bc548 @ 0x020bc548, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f87c0[];
extern struct UnkStruct_020bc548 {
    int unk_00;
    int unk_04;
} data_021f75b0;
extern int _s32_div_f(int, int);

void func_020bc548(unsigned char *param)
{
    unsigned short *ptr;
    unsigned short *end1;
    unsigned short *end2;
    unsigned char byte;
    unsigned short value;
    int mult;
    int i;
    int tmp;

    ptr = (unsigned short *) (data_021f87c0 + data_021f75b0.unk_04 * 0x180);
    end1 = (unsigned short *) ((char *) ptr + 0xee);
    end2 = (unsigned short *) ((char *) ptr + 0x12e);
    byte = param[0x2f51];
    value = (unsigned short) (byte | 0x1000);

    while (ptr < end1) {
        *ptr++ = value;
    }

    mult = _s32_div_f(-((int) byte << 12), 0x20);
    i = 0;
    while (ptr < end2) {
        tmp = ((mult * i + 0x800) >> 12) + byte;
        *ptr++ = (unsigned short) (tmp | 0x1000);
        i++;
    }
}
