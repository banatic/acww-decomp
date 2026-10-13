/* func_ov003_022171dc @ 0x022171dc, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022171dc(void *r0, void *r1, unsigned short r2);

void func_ov003_022171dc(void *r0, void *r1, unsigned short r2)
{
    unsigned int r3;
    unsigned int r1_8;

    r3 = *(unsigned int *) r1;
    *(unsigned int *) r0 = r3;
    r3 = *(unsigned int *) ((char *) r1 + 4);
    *(unsigned int *) ((char *) r0 + 4) = r3;
    r1_8 = *(unsigned int *) ((char *) r1 + 8);
    *(unsigned int *) ((char *) r0 + 8) = r1_8;
    *(unsigned short *) ((char *) r0 + 12) = r2;
}
