/* field_actor_45: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022171dc @ 0x022171dc, 0x10 bytes, Thumb
 * func_ov003_022171c4 @ 0x022171c4, 0x16 bytes, Thumb
 * func_ov003_022171ac @ 0x022171ac, 0x18 bytes, Thumb
 */

extern void func_020779b8(void *unused0, int unused1, int unused2);
extern void func_02077978(const unsigned char *data, unsigned int *first, unsigned int *second);

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

void func_ov003_022171c4(unsigned char *r0, int r1, int r2, unsigned char r3)
{
    unsigned char r4 = r3;
    unsigned char *r5 = r0;
    func_020779b8(r0, r1, r2);
    r5[5] = r4;
}

void func_ov003_022171ac(const unsigned char *r0, unsigned int *r1, unsigned int *r2, unsigned char *r3)
{
    const unsigned char *r5 = r0;
    unsigned char *r4_ptr = r3;
    func_02077978(r0, r1, r2);
    *r4_ptr = r5[5];
}
