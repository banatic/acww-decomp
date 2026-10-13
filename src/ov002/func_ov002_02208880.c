/* func_ov002_02208880 @ 0x02208880, 0x1a bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208880(void *r0, unsigned short r1, unsigned short r2, unsigned short r3);

void func_ov002_02208880(void *r0, unsigned short r1, unsigned short r2, unsigned short r3)
{
    unsigned char r4 = 0;
    ((unsigned char *) r0)[0xe] = r4;
    ((unsigned char *) r0)[0xf] = r4;
    ((unsigned char *) r0)[0x10] = r4;
    ((unsigned short *) r0)[0x5] = r4; // offset 0xa
    ((unsigned short *) r0)[0x6] = r4; // offset 0xc
    ((unsigned short *) r0)[0x2] = r1; // offset 4
    ((unsigned short *) r0)[0x3] = r2; // offset 6
    ((unsigned short *) r0)[0x4] = r3; // offset 8
}
