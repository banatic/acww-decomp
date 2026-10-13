/* func_020b1d54 @ 0x020b1d54, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern unsigned short *func_ov004_022320d8(int p0);
extern void func_02062300(unsigned short *);

void func_020b1d54(int p0)
{
    unsigned int flag;
    unsigned short value;
    if (p0 == 0x1a) {
        flag = (data_020e54a8 == 1) ? 1u : 0u;
        if (flag == 0) {
            return;
        }
        value = *func_ov004_022320d8(p0);
        func_02062300(&value);
    }
}
