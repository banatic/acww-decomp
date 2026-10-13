/* func_0209d498 @ 0x0209d498, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d83c(void *data, int param);

extern unsigned char data_021dc6e8[];

void func_0209d498(unsigned char *arg)
{
    if (*arg) {
        func_0209d83c((void *) data_021dc6e8, 2);
    } else {
        func_0209d83c((void *) data_021dc6e8, 1);
    }
}
