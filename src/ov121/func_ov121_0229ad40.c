/* func_ov121_0229ad40 @ 0x0229ad40, 0x28 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov121_0229ad40(short *r0)
{
    short *r1;
    short r2;
    unsigned char r3;

    r2 = *(short *) ((char *) r0 + 0xa8);
    r3 = data_021f6c58;
    r2 += r3;
    r1 = (short *) ((char *) r0 + 0xa4);
    *r1 = r2;

    r2 = *(short *) ((char *) r0 + 0xaa);
    r3 = data_021f6c54;
    r2 += r3;
    r0 = (short *) ((char *) r0 + 0xa6);
    *r0 = r2;
}
