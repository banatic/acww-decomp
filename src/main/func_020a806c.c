/* func_020a806c @ 0x020a806c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c60;
extern unsigned char data_021f6c5c;
extern int func_020a7dac(void);

int func_020a806c(int *a, int *b)
{
    int result = 0;
    int flag;

    if (func_020a7dac() == 0) {
        if (data_021fbdd8 != 0 && data_021fbddc != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag != 0) {
            int v1 = data_021f6c60;
            int v2 = data_021f6c5c;
            if (a) {
                *a = v1;
            }
            if (b) {
                *b = v2;
            }
            result = 1;
        }
    }
    return result;
}
