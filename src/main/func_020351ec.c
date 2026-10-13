/* func_020351ec @ 0x020351ec, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern unsigned int data_021c526c;
extern void func_020368c0(unsigned int);
extern void func_02036788(unsigned int);

void func_020351ec(void)
{
    unsigned int tmp;
    unsigned int cond;
    unsigned int cond2;

    tmp = data_020e54a8;
    if (tmp == 0) {
        cond = 1;
    } else {
        cond = 0;
    }

    if (cond != 0) {
        func_020368c0(data_021c526c + 0x264);
    } else {
        if (tmp == 1) {
            cond2 = 1;
        } else {
            cond2 = 0;
        }

        if (cond2 != 0) {
            func_02036788(data_021c526c + 0x2a0);
        }
    }
}
