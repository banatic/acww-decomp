/* func_0209b42c @ 0x0209b42c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209bd44(void);
extern int func_0209bc94(int);
extern int func_0209bc40(int);
extern int func_0209bc44(int, int *);
extern unsigned int func_0209bba0(int);
extern unsigned char data_020e3514[];

int func_0209b42c(int a, int b)
{
    int flag = 0;
    int local;
    if (func_0209bd44() != 0) {
        if (func_0209bc94(b) == 1) {
            if (b == func_0209bc40(a)) {
                if (func_0209bc44(a, &local) != 0) {
                    if (func_0209bba0(a) > data_020e3514[local * 20]) {
                        flag = 1;
                    }
                }
            }
        }
    }
    return flag;
}
