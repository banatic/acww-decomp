/* func_0209c2d4 @ 0x0209c2d4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_0209c310(unsigned char arg0);

extern unsigned char data_020d1a20[];

int func_0209c2d4(unsigned char *arg0, unsigned char arg1)
{
    unsigned char local_1;
    int local_2;
    unsigned char local_3;

    local_3 = func_0209c310(arg1);
    *arg0 = local_3;
    local_1 = *arg0;
    if (local_1 < 3) {
        local_2 = arg1 - data_020d1a20[local_1];
    } else {
        local_2 = -1;
    }
    return local_2;
}
