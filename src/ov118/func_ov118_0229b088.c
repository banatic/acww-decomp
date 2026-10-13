/* func_ov118_0229b088 @ 0x0229b088, 0x60 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

int func_ov118_0229b088(char *p, int arg1, int arg2)
{
    int i;

    for (i = 0; i < 14; i++) {
        unsigned char *e = (unsigned char *) (p + i * 3);
        if (e[0x47af] == 0xc) {
            continue;
        }
        if (e[0x47ad] - 8 >= arg1) {
            continue;
        }
        if (e[0x47ad] + 8 <= arg1) {
            continue;
        }
        if (e[0x47ae] - 8 >= arg2) {
            continue;
        }
        if (e[0x47ae] + 8 <= arg2) {
            continue;
        }
        return (unsigned char) i;
    }
    return 14;
}
