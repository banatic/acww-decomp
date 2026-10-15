/* func_02074228 @ 0x02074228, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073bf4(int, int, int);
extern unsigned int func_02073044(void);
extern int func_020ec338(unsigned short, int, int);

void func_02074228(unsigned int arg1)
{
    int i = 3;
    int a = data_020ccf94;
    do {
        if (i < arg1) {
            int t = func_02073bf4(a, i, 0);
            func_02073044();
            func_020ec338((unsigned short) i, t, 0x1000);
        } else if (i > arg1) {
            int t = func_02073bf4(a, i - 1, 0);
            func_02073044();
            func_020ec338((unsigned short) i, t, 0x1000);
        }
        i--;
    } while (i >= 0);
}
