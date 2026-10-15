/* func_ov095_0229b058 @ 0x0229b058, 0x38 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d34(void *, int, int, int, int);

extern unsigned char data_021f6c54[];
extern unsigned char data_021f6c58[];
extern unsigned char data_ov095_0229e380[];

int func_ov095_0229b058(void *p)
{
    return func_02088d34((void *) data_ov095_0229e380, *((const unsigned char *) data_021f6c58) - 0x80,
                         *((const unsigned char *) data_021f6c54) - 0x60, 0, 0) != 0;
}
