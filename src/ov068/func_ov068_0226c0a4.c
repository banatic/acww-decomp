/* func_ov068_0226c0a4 @ 0x0226c0a4, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov003_02219be0(unsigned int);

int func_ov068_0226c0a4(unsigned int param)
{
    unsigned int x;
    x = func_ov003_02219be0(param);
    if ((x >= 0x12e8u && x <= 0x131fu) || (x >= 0x12b0u && x <= 0x12e7u)) {
        return 1;
    } else {
        return 0;
    }
}
