/* func_02093a50 @ 0x02093a50, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209418c(int, int, int, int, void *, void *, void (*)(void *));
extern void func_02093a78(void *);
extern unsigned char data_020e287c[];
extern unsigned char data_020e2784[];

void func_02093a50(int a, int b, int c, int d)
{
    func_0209418c(a, b, c, d, &data_020e287c, &data_020e2784, func_02093a78);
}
