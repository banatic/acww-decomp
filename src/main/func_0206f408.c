/* func_0206f408 @ 0x0206f408, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short data_021cfc1c[];
extern unsigned char data_021cfc14;
extern char data_021cfc2c;
extern unsigned char data_027e0438[24];
extern int func_0205bfdc(char *);
extern void func_02001ca0(int, int, int, int);

#define REG_BLDY (*(volatile unsigned short *) 0x04000042)

void func_0206f408(void)
{
    int i;
    int level;

    if (data_021cfc1c[0] > 20) {
        data_021cfc1c[0] -= 20;
    } else {
        func_0205bfdc(&data_021cfc2c);
        data_021cfc14 &= ~1;
        func_02001ca0(0, 0, 0xff, 0xc0);
        REG_BLDY = 0xff;
        data_021cfc1c[0] = 0;
    }
    for (i = 0; i < 24; i++) {
        level = data_021cfc1c[0] - i;
        if (level < 0) {
            data_027e0438[i] = 0;
        } else if (level > 0xfe) {
            data_027e0438[i] = 0xfe;
        } else {
            data_027e0438[i] = level;
        }
    }
    REG_BLDY = ((data_027e0438[0] << 8) & 0xff00) | 0xff;
}
