/* func_02072180 @ 0x02072180, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064328(void *dest, const void *src, int n);
extern int func_02064af4(void *dest, const void *src, int n);
extern const char data_020e17c0[];

int func_02072180(const void *arg0, int arg1)
{
    char buf[0x28];

    func_02064328(buf, data_020e17c0, arg1 + 2);
    return func_02064af4(buf, arg0, 0x200);
}
