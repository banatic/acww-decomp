/* func_ov003_0220c160 @ 0x0220c160, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov003_0223c5a0;
extern unsigned int data_ov003_0223c5f4[8];

void func_ov003_0220c160(void)
{
    unsigned int i;
    unsigned int zero;

    if (data_ov003_0223c5a0 == 0) {
        i = 0;
        zero = 0;
        do {
            data_ov003_0223c5f4[i] = zero;
            i++;
        } while (i < 8);
    }
}
