/* func_0202f188 @ 0x0202f188, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c30b0;
extern int data_021c30b4;
extern int PM_GetBattery(int *);

int func_0202f188(void)
{
    int result = 0;
    int local;

    if (data_021c30b0) {
        goto out;
    }

    if (--data_021c30b4 > 0) {
        goto out;
    }
    data_021c30b4 = 20;

    if (PM_GetBattery(&local) != 0) {
        goto out;
    }
    if (local != 1) {
        goto out;
    }
    result = 1;

out:
    return result;
}
