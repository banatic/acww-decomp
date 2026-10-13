/* func_0209cc84 @ 0x0209cc84, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209cc30(int a, int b, int c);
extern int func_0209d034(void);
extern int data_020d1ac0[];

int func_0209cc84(int arg)
{
    unsigned int i, j, k;
    unsigned int base = 1;
    for (i = base; i < 5; i++) {
        for (j = base; j < 5; j++) {
            for (k = 0; k < 6; k++) {
                func_0209cc30(arg, j, i);
                if (data_020d1ac0[k] == func_0209d034()) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
