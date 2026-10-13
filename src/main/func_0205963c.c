/* func_0205963c @ 0x0205963c, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205996c(void *a, void *b, int c);
int func_0205963c(unsigned char *param0, unsigned char param1, void *param2)
{
    int ret = 0;
    if (param0[200] != 0) {
        if (param0[217] != 1) {
            if (func_0205996c(param0, param2, 0) == 1) {
                param0[88] = param1;
                ret = 1;
            }
        }
    }
    return ret;
}
