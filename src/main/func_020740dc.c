/* func_020740dc @ 0x020740dc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073dd4(int, int);
extern int func_02073918(int, int);

int func_020740dc(void)
{
    int r5 = 0;
    int r4 = 3;
    int r6 = data_020ccf94;
    int r7 = 1;
    do {
        if (func_02073dd4(r6, r4) != 0) {
            if (func_02073918(r6, r4) == 0) {
                r5 |= (unsigned char) (r7 << r4);
            }
        }
        r4--;
    } while (r4 >= 0);
    return r5;
}
