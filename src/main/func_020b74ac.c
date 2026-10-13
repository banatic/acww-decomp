/* func_020b74ac @ 0x020b74ac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov003_022201e4(int arg);

int func_020b74ac(int p)
{
    unsigned int flag = (data_020e54a8 == 0) ? 1 : 0;
    if (flag > 0) {
        return func_ov003_022201e4(p);
    } else {
        return 0;
    }
}
