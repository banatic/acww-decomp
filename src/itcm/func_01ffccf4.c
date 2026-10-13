/* func_01ffccf4 @ 0x01ffccf4, 0x58 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_027e0434;
extern unsigned char data_027e0438[];

void func_01ffccf4(void)
{
    volatile unsigned short *regs;
    unsigned int c;
    unsigned char val;
    unsigned int combined;

    c = data_027e0434;
    regs = (volatile unsigned short *) 0x04000000;
    val = data_027e0438[(c >= 0x18) ? (0x2f - c) : c];
    combined = (((unsigned int) val << 8) & 0xff00) | 0xff;
    c = c + 1;
    if (regs[2] & 2) {
        regs[0x21] = (unsigned short) combined;
    }
    if (c >= 0x30) {
        c = c - 0x30;
    }
    data_027e0434 = (unsigned char) c;
}
