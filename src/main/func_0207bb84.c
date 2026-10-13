/* func_0207bb84 @ 0x0207bb84, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02079924(int, int, int);
extern int data_020cd474[4];

int func_0207bb84(int p, int e0, int e1)
{
    int ret;
    int i;
    p = func_02079924(p + 0x3f60, e0, e1);
    ret = 4;
    for (i = 0; i < 4; i++) {
        if (p >= data_020cd474[i]) {
            ret = i;
            break;
        }
    }
    return ret;
}