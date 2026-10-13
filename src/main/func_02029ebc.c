/* func_02029ebc @ 0x02029ebc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(unsigned short *p);

int func_02029ebc(unsigned short *param)
{
    int result = 0;

    if (func_0204bcdc(param)) {
        int inRange = 0;

        if (*param >= 0x450cu && *param <= 0x45dbu) {
            inRange = 1;
        }
        if (!inRange) {
            result = 1;
        }
    }
    return result;
}
