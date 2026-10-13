/* func_02073220 @ 0x02073220, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_02077b58(unsigned int param1);

unsigned short func_02073220(unsigned int param1, unsigned int param2)
{
    unsigned int temp;
    unsigned short result;

    temp = func_02077b58(param2);
    temp = temp << 1;
    result = *(unsigned short *) ((unsigned char *) param1 + temp + 0x128);
    return result;
}
