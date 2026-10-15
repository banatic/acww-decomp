/* func_0206f38c @ 0x0206f38c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_027e0438[];
extern short data_021cfc1c;
extern unsigned char data_021cfc14;
extern int data_021cfc2c;

extern int func_0205bfdc(void *p);

void func_0206f38c(void)
{
    int i;
    int v;
    int d;

    if (data_021cfc1c < 0x103) {
        data_021cfc1c = (short) (data_021cfc1c + 0x14);
    } else {
        func_0205bfdc(&data_021cfc2c);
        data_021cfc14 &= ~1;
        data_021cfc1c = 0xfe;
        *(unsigned short *) 0x04000042 = 0xfeff;
    }
    i = 0;
    v = data_021cfc1c;
    for (; i < 0x18; i++) {
        d = v - i;
        if (d < 0) {
            data_027e0438[i] = 0;
        } else if (d > 0xfe) {
            data_027e0438[i] = 0xfe;
        } else {
            data_027e0438[i] = (unsigned char) d;
        }
    }
}
