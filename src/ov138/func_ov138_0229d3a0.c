/* func_ov138_0229d3a0 @ 0x0229d3a0, 0x44 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int);
extern void *func_ov002_0220830c(void *);
extern void *func_ov002_02209ccc(void *);
extern void *func_ov002_0220b008(void *);
extern void *func_ov134_0229bed4(void *);
extern char data_ov138_0229d4e0[];

void *func_ov138_0229d3a0(void)
{
    void *p = func_ov002_02207f80(0x2b78);
    if (p) {
        func_ov002_0220830c(p);
        *(void **) p = data_ov138_0229d4e0;
        func_ov002_02209ccc((char *) p + 0x98);
        func_ov002_0220b008((char *) p + 0xfc);
        func_ov134_0229bed4((char *) p + 0x2c8);
    }
    return p;
}
