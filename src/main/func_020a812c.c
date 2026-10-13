/* func_020a812c @ 0x020a812c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7dac(void);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

int func_020a812c(void)
{
    int result = 0;
    if (func_020a7dac() == 0) {
        unsigned int cond = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
        if (cond > 0) {
            result = 1;
        }
    }
    return result;
}
