/* func_020eb7ac @ 0x020eb7ac, 0x98 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc;
extern unsigned char data_021fbef8;
extern unsigned char data_021fbef4;

extern void func_020ed5f8(int argument0, int argument1);
extern void func_020ed5f4(void);
extern void func_020ed68c(int size, int peer);
extern void func_020ed658(int argument0, int argument1, int argument2);
extern void func_020ed6a8(int status, int local, int cancelled, int peer, int connection, void *userData);

extern void func_ov065_02277e7c(unsigned char, void (*)(), int, void (*)(), int);
extern void *func_ov065_0227ed18(void (*)(int, int));
extern void *func_ov065_0227ed04(void (*)(int, int, int));
extern void func_ov065_02277d38(void (*)(int, int, int, int, int, void *), void *);

int func_020eb7ac(void)
{
    if (data_021fbefc < 4) {
        return 0;
    }
    data_021fbef8 = 3;
    func_ov065_02277e7c(data_021fbef4, func_020ed5f8, 0, func_020ed5f4, 0);
    func_ov065_0227ed18(func_020ed68c);
    func_ov065_0227ed04(func_020ed658);
    func_ov065_02277d38(func_020ed6a8, 0);
    return 1;
}
