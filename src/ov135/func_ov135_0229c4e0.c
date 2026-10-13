/* func_ov135_0229c4e0 @ 0x0229c4e0, 0x38 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229beb0(void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220826c(void *);
extern unsigned int data_ov135_0229d610;

void *func_ov135_0229c4e0(void *p)
{
    *(unsigned int *) p = (unsigned int) &data_ov135_0229d610;
    func_ov134_0229beb0((char *) p + 0x2c8);
    func_ov002_0220afdc((char *) p + 0xfc);
    func_ov002_02209cb4((char *) p + 0x98);
    func_ov002_0220826c(p);
    return p;
}
