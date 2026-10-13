/* func_ov130_0229a278 @ 0x0229a278, 0x3c bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov130_0229a80c[];

int func_ov130_0229a278(unsigned char *p, int x, int y)
{
    int nx = x - 0x50;
    int ny = y - 0x60;

    if (p[8] == 0 || p[8] == 2) {
        nx -= 0x40;
    }

    if (nx >= 0 && nx < 0x60 && ny >= 0 && ny < 0x40) {
        p[4] = data_ov130_0229a80c[(nx >> 5) + 3 * (ny >> 4)];
        return p[4];
    }
    return 13;
}
