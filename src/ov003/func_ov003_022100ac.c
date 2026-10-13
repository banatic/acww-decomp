/* func_ov003_022100ac @ 0x022100ac, 0x16 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void func_ov003_022100ac(void *r0, unsigned char r1, unsigned short r2, void *r3)
{
    ((unsigned char *) r0)[0xf] = r1;
    ((unsigned char *) r0)[0xe] = 0;
    *(unsigned short *) ((char *) r0 + 0xc) = r2;
    *(unsigned int *) r0 = *(unsigned int *) r3;
    *(unsigned int *) ((char *) r0 + 4) = *(unsigned int *) ((char *) r3 + 4);
    *(unsigned int *) ((char *) r0 + 8) = *(unsigned int *) ((char *) r3 + 8);
}
