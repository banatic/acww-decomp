/* func_0206f2f0 @ 0x0206f2f0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short data_021cfc1c;             // 0x021cfc1c
extern unsigned char data_021cfc14;     // 0x021cfc14
extern unsigned char data_027e0438[24]; // 0x027e0438
extern unsigned char data_027e0434;     // 0x027e0434

extern int func_0205c024(void *a, void *b, void (*c)(void), int d);
extern void func_0206f408(void);
extern void func_02001ca0(int a, int b, int c, int d);

extern unsigned char data_021cfc2c[];
extern void func_01ffccf4(void);

void func_0206f2f0(void)
{
    int i;

    data_021cfc1c = 0x117;
    if (func_0205c024((void *) data_021cfc2c, (void *) func_01ffccf4, func_0206f408, 0) != 0) {
        data_021cfc14 |= 1;
    }

    for (i = 0; i < 24; i++) {
        data_027e0438[i] = 0xFE;
    }

    func_02001ca0(data_021cfc1c, 0, 0xFF, 0xC0);
    data_027e0434 = 0;
}
