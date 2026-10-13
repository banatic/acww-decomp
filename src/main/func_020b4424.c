/* func_020b4424 @ 0x020b4424, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f4dac;
extern int func_020b42a0(int *, int);
extern int func_020b4218(int *);

int func_020b4424(int param)
{
    int result = 0;
    if (func_020b42a0(&data_021f4dac, param)) {
        result = func_020b4218(&data_021f4dac);
    }
    return result;
}
