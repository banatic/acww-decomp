/* func_020a9b04 @ 0x020a9b04, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;

void func_020a9b04(unsigned int *r0)
{
    unsigned int r1;
    unsigned char r2;

    r1 = 0;
    r1 = ~r1;
    r0[1] = r1;

    r2 = data_021f43ec;
    *((unsigned char *) r0 + 8) = r2;

    r1 = data_021f43ec;
    *((unsigned char *) r0 + 9) = (unsigned char) r1;
}
