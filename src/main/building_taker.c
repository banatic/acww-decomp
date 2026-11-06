/* building_taker: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b3b38 @ 0x020b3b38, 0x18 bytes, Thumb
 * func_020b3b20 @ 0x020b3b20, 0x18 bytes, Thumb
 * func_020b3b14 @ 0x020b3b14, 0xc bytes, Thumb
 */

extern int data_021f4b2c;

int func_020b3b38(void *arg)
{
    if ((*(void **) &data_021f4b2c) == 0) {
        (*(void **) &data_021f4b2c) = arg;
        return 1;
    }
    return 0;
}

int func_020b3b20(void *param)
{
    if (data_021f4b2c) {
        data_021f4b2c = 0;
        return 1;
    }
    return 0;
}

int func_020b3b14(void)
{
    return data_021f4b2c;
}
