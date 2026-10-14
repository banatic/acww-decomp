/* func_ov113_022995a0 @ 0x022995a0, 0x50 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209c60(void *p);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*cb)(void));
extern void func_02070be8(void);
extern void func_ov002_0220826c(void *p);

extern unsigned char data_ov113_0229ac00[];

void *func_ov113_022995a0(void *p)
{
    *(unsigned int *) p = (unsigned int) data_ov113_0229ac00;
    func_ov002_02209c60((char *) p + 0x2b20);
    __cxa_vec_cleanup((char *) p + 0x2898, 6, 0x6c, func_02070be8);
    __cxa_vec_cleanup((char *) p + 0x26e8, 4, 0x6c, func_02070be8);
    func_ov002_0220826c(p);
    return p;
}
