/* func_0206f28c @ 0x0206f28c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc1c;
extern unsigned char data_021cfc14;
extern unsigned char data_027e0438[0x18];
extern unsigned char data_027e0434;
extern unsigned int data_021cfc2c;
extern unsigned int func_01ffccf4;
extern int func_0205c024(void *, void *, void (*)(void), int);
extern void func_0206f38c(void);
extern void func_02001ca0(int, int, int, int);

void func_0206f28c(void)
{
    int i;
    int val;

    data_021cfc1c = 0;
    if (func_0205c024(&data_021cfc2c, &func_01ffccf4, func_0206f38c, 0) != 0) {
        data_021cfc14 |= 1;
    }
    i = 0;
    val = i;
    while (i < 0x18) {
        data_027e0438[i] = val;
        i++;
    }
    func_02001ca0(1, val, 0xff, 0xc0);
    data_027e0434 = 0;
}