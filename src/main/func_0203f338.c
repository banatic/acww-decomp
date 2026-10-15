/* func_0203f338 @ 0x0203f338, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_020a7278(void);

int func_0203f338(void)
{
    int r = func_02073d90(data_020ccf94);

    if (r == 0) {
        return 2;
    }
    if (!func_020a7278()) {
        return 1;
    }
    return 2;
}
