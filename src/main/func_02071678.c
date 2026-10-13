/* func_02071678 @ 0x02071678, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cec0(void *ptr, int param);
extern int func_02081500(int arg);
extern char data_021e5a2c[];

int func_02071678(int param)
{
    int ret;

    ret = func_0207cec0(data_021e5a2c, param);
    if (ret != 0) {
        return func_02081500(ret);
    }
    return 0;
}
