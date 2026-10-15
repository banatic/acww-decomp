/* func_0207252c @ 0x0207252c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021d054c[4][8];
extern int data_021d04e4[8];

void func_0207252c(void *receiver)
{
    unsigned char i, j, k;
    k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            data_021d054c[i][j] = k;
        }
    }
    for (k = 0; k < 8; k++) {
        data_021d04e4[k] = 0;
    }
}
