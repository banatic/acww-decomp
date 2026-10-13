/* func_02057b08 @ 0x02057b08, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020dd19c[];

int func_02057b08(unsigned int param)
{
    return data_020dd19c[(param & 0x00700000) >> 20] * data_020dd19c[(param & 0x03800000) >> 23];
}
