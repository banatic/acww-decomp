/* func_02052ee8 @ 0x02052ee8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02052f3c(unsigned char);
void func_02053060(int, int, int, int, int);

void func_02052ee8(int a0, int a1, int a2, int a3, unsigned char a4)
{
    int tmp;
    tmp = func_02052f3c(a4);
    if (tmp != 0) {
        func_02053060(tmp, a0, a1, a2, a3);
    }
}
