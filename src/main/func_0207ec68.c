/* func_0207ec68 @ 0x0207ec68, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cad4(void *ptr);
extern int data_021e5a2c;

int func_0207ec68(void)
{
    int ret = 0;
    if (func_0207cad4(&data_021e5a2c) <= 4) {
        ret = 1;
    }
    return ret;
}
