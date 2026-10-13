/* func_ov094_0229b328 @ 0x0229b328, 0x5c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

int func_ov094_0229b328(int arg0, int key)
{
    if (key >= 0 && key <= 9) {
        return 0x3c + 24 * (key >> 1);
    }
    if (key >= 10 && key <= 34) {
        int count;
        key -= 10;
        count = 0;
        while (key >= 5) {
            key -= 5;
            count++;
        }
        return 0x3c + 24 * count;
    }
    if (key >= 35 && key <= 44) {
        return 0x3c + 24 * ((key - 35) >> 1);
    }
    if (key >= 45 && key <= 54) {
        return 0x3c + 24 * ((key - 45) >> 1);
    }
    return 0;
}
