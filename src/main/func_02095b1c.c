/* func_02095b1c @ 0x02095b1c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_02009d38(int, int, int, int);

int func_02095b1c(unsigned short *arg0)
{
    int ret = func_02096718(4);
    if (ret != 0) {
        ret = func_02009d38(ret, *arg0, 6, -1);
    } else {
        ret = 0;
    }
    return ret;
}
