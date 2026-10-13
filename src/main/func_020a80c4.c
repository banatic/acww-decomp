/* func_020a80c4 @ 0x020a80c4, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char func_020a7dac(void);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c60;
extern unsigned char data_021f6c5c;

int func_020a80c4(int r0, int r1, int r2, int r3)
{
    int result;
    int r4 = 0;
    int r5 = r0;
    int r6 = r1;
    int r7 = r2;
    int sp_val = r3;

    if (func_020a7dac() == 0) {
        if (data_021fbdd8 != 0 && data_021fbddc != 0) {
            result = 1;
        } else {
            result = 0;
        }

        if (result != 0) {
            unsigned char a = data_021f6c60;
            unsigned char b = data_021f6c5c;

            if (a >= r5 && a < r6 && b >= r7 && b < sp_val) {
                r4 = 1;
            }
        }
    }

    return r4;
}
