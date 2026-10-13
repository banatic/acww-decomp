/* func_02040ba0 @ 0x02040ba0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02040980(unsigned char *param);
extern unsigned char data_021f39c0[];

void func_02040ba0(unsigned int param)
{
    if (param >= 62 && param < 70) {
        unsigned char *p = func_02040980(data_021f39c0);
        if (p != 0) {
            if (param == p[2]) {
                p[4] = 1;
            }
        }
    }
}
