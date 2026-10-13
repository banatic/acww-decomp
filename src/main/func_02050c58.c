/* func_02050c58 @ 0x02050c58, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_02050c58(void *param1, void *param2);

unsigned short func_02050c58(void *param1, void *param2)
{
    unsigned short result;
    signed char c1;
    signed char c2;
    unsigned int val;
    unsigned int val2;
    unsigned int val3;

    c1 = *(signed char *) param2;
    c2 = *(signed char *) ((char *) param2 + 1);
    val = (unsigned int) c1 & 0xff;
    val2 = ((unsigned int) c2 << 8) & 0x0000ff00;
    val3 = val | val2;
    result = (unsigned short) val3;
    *(unsigned short *) param1 = result;
    return 2;
}
