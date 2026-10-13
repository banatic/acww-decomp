/* func_02065ec0 @ 0x02065ec0, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_02065ec0(unsigned char *param);

unsigned char func_02065ec0(unsigned char *param)
{
    unsigned char val;
    unsigned char result;

    val = *(param + 0xfa);
    result = val & 0x3f;
    return result;
}
