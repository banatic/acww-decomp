/* func_02052fdc @ 0x02052fdc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d20cc;
extern int func_02052ff4(unsigned char);

int func_02052fdc(unsigned char arg)
{
    return func_02052ff4(data_020d20cc + arg);
}
