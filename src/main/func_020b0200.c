/* func_020b0200 @ 0x020b0200, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *ptr);
extern unsigned char *data_020ccf94;

void func_020b0200(unsigned char *param)
{
    unsigned char *base;

    param[1] = 0;
    base = data_020ccf94;
    if (func_02073d90(base)) {
        base += 0x6c;
        param[0] = *base - 1;
    } else {
        param[0] = 0;
    }
}
