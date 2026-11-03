/* spawner_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02083f84 @ 0x02083f84, 0x20 bytes, Thumb
 * func_02083f68 @ 0x02083f68, 0x1c bytes, Thumb
 * func_02083f40 @ 0x02083f40, 0x26 bytes, Thumb
 */

extern int func_02083fa4(void *dst, const void *src, int size, int flag);
extern unsigned char data_020d0654[];
extern unsigned char data_020d0684[];
extern unsigned char data_020d064c[];
extern int func_020984e8(void);
extern int func_0209967c(int object);
extern int func_020887c0(int a, int b);

void func_02083f84(void)
{
    func_02083fa4((void *) data_020d0684, (const void *) data_020d0654, 4, 1);
}

void func_02083f68(void)
{
    func_02083fa4((void *) data_020d064c, 0, 1, 1);
}

int func_02083f40(void)
{
    int object;
    if ((object = func_020984e8()) != 0) {
        if (func_020887c0(func_0209967c(object), 0x18) == 0) {
            return 1;
        }
    }
    return 0;
}
