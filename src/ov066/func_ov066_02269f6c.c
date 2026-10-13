/* func_ov066_02269f6c @ 0x02269f6c, 0xa0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern unsigned int func_ov066_0226a278(void);
extern unsigned int func_ov066_022699ec(void);
extern unsigned char data_ov066_0226bdfc;
extern unsigned short data_ov066_0226be00;
extern unsigned char *data_ov066_0226bdf4;

int func_ov066_02269f6c(void)
{
    unsigned short bits;
    unsigned char rem, i;

    if (func_ov066_0226a278() != 0) {
        goto ret0;
    }
    if (data_ov066_0226bdfc == 0) {
        goto ret0;
    }
    i = 0;
    rem = (unsigned char) (func_ov066_022699ec() % data_ov066_0226bdfc);
    bits = data_ov066_0226be00;
    do {
        if ((bits & (1U << i)) != 0) {
            if (rem != 0) {
                rem = (unsigned char) (rem - 1);
            } else {
                data_ov066_0226bdf4[0x8d] = (unsigned char) (i + 1);
                goto ret1;
            }
        }
        i = (unsigned char) (i + 1);
    } while (i < 14);
ret0:
    return 0;
ret1:
    return 1;
}
