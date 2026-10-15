/* func_0202e468 @ 0x0202e468, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e550(void *);
extern int func_02064328(void *a, void *b, int c, int d);
extern char data_021c1da4[];
extern char data_020d9fc0[];

void *func_0202e468(void *argument0)
{
    int x = func_0202e550((void *) argument0);
    if (x == -1) {
        x = 0;
    }
    func_02064328(data_021c1da4, data_020d9fc0, x & 0xf8, x);
    return data_021c1da4;
}
