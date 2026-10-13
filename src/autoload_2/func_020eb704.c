/* func_020eb704 @ 0x020eb704, 0xa8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc;
extern unsigned char data_021fbef8;

extern int func_020eb8a0(int a);

extern void func_020ed6ac(void);
extern void func_020ed5f4(void);
extern void func_020ed68c(void);
extern void func_020ed658(void);
extern void func_020ed6a8(void);

extern void func_ov065_02277d50(int, void (*)(void), int, void (*)(void), int);
extern void func_ov065_0227ed18(void (*)(void));
extern void func_ov065_0227ed04(void (*)(void));
extern void func_ov065_02277d38(void (*)(void), int);

int func_020eb704(int a)
{
    int ret;

    if (data_021fbefc != 4) {
        return 0;
    }

    data_021fbef8 = 4;

    ret = func_020eb8a0(a);
    if (ret == -1) {
        return 0;
    }

    func_ov065_02277d50(ret, func_020ed6ac, 0, func_020ed5f4, 0);
    func_ov065_0227ed18(func_020ed68c);
    func_ov065_0227ed04(func_020ed658);
    func_ov065_02277d38(func_020ed6a8, 0);

    return 1;
}