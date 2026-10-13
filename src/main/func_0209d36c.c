/* func_0209d36c @ 0x0209d36c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021dc6c4;
extern unsigned char data_021dc6c8;
extern unsigned char data_021fbe38;

void func_0209d36c(void)
{
    if (data_021dc6c4 == 0) {
        if (data_021dc6c8 != 0) {
            if (data_021fbe38 == 0) {
                data_021dc6c8 = 0;
                return;
            }
        } else {
            if (data_021fbe38 != 0) {
                data_021dc6c4 = 1;
                data_021dc6c8 = 1;
            }
        }
    }
}
