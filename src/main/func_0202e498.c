/* func_0202e498 @ 0x0202e498, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e550(void);
extern void func_02064328(void *a, void *b, int c, int d);
extern char data_021c1d84[];
extern char data_020d9fd8[];

void *func_0202e498(void)
{
    int x = func_0202e550();
    if (x == -1) {
        x = 0;
    }
    func_02064328(data_021c1d84, data_020d9fd8, x & 0xf8, x);
    return data_021c1d84;
}
