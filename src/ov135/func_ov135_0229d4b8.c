/* func_ov135_0229d4b8 @ 0x0229d4b8, 0x44 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_0220b008(void *p);
extern void *func_ov134_0229bed4(void *p);

extern int data_ov135_0229d610;

void *func_ov135_0229d4b8(void)
{
    void *r4;
    r4 = func_ov002_02207f80(0x2b78);
    if (r4 != 0) {
        func_ov002_0220830c(r4);
        *(unsigned int *) r4 = (unsigned int) &data_ov135_0229d610;
        func_ov002_02209ccc((void *) ((unsigned int) r4 + 0x98));
        func_ov002_0220b008((void *) ((unsigned int) r4 + 0xFC));
        func_ov134_0229bed4((void *) ((unsigned int) r4 + 0x2C8));
    }
    return r4;
}
