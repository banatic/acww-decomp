/* battery_warning: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202f188 @ 0x0202f188, 0x44 bytes, Thumb
 * func_0202f17c @ 0x0202f17c, 0xc bytes, Thumb
 * func_0202f164 @ 0x0202f164, 0x18 bytes, Thumb
 */

extern int data_021c30b4;
extern int PM_GetBattery(int *);
extern unsigned char data_021c30b0[];

int func_0202f188(void)
{
    int result = 0;
    int local;

    if ((*(unsigned char *) data_021c30b0)) {
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

void func_0202f17c(void)
{
    unsigned char *ptr;
    ptr = (unsigned char *) data_021c30b0;
    *ptr = 1;
}

void func_0202f164(void)
{
    (*(volatile unsigned char *) data_021c30b0) = 0;
    (*(volatile unsigned int *) &data_021c30b4) = 0x14;
}
