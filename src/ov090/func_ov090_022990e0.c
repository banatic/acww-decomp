/* func_ov090_022990e0 @ 0x022990e0, 0x74 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int _s32_div_f(int, int);

int func_ov090_022990e0(void)
{
    unsigned int ok;
    int x, y, q;

    ok = (data_021fbdd8 && data_021fbddc);
    if (ok == 0) {
        return -1;
    }

    x = data_021f6c58;
    y = data_021f6c54;
    if (y > 16) {
        return -1;
    }
    if (x < 53) {
        return -1;
    }
    if (x >= 256) {
        return -1;
    }

    x -= 53;
    q = _s32_div_f(x, 25);
    if (q < 7) {
        return q;
    }
    return 7;
}
