/* func_020a8028 @ 0x020a8028, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7dac(void);
extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

int func_020a8028(int *param1, int *param2)
{
    int result = 0;
    int r5 = (int) param1;
    int r4 = (int) param2;

    if (func_020a7dac() == 0) {
        if (data_021fbdd8 != 0) {
            unsigned char r1 = data_021f6c58;
            unsigned char r0 = data_021f6c54;
            if (r5 != 0) {
                *(int *) r5 = r1;
            }
            if (r4 != 0) {
                *(int *) r4 = r0;
            }
            result = 1;
        }
    }
    return result;
}
