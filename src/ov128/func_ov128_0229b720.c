/* func_ov128_0229b720 @ 0x0229b720, 0x54 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070be8(void *);
extern void func_ov127_0229a0e8(void *);
extern void func_020b18a8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220b3a4(void *);
extern void func_ov002_0220826c(void *);
extern int data_ov128_0229cbc0;

void *func_ov128_0229b720(void *self)
{
    char *p = (char *) self;
    *(unsigned int *) p = (unsigned int) &data_ov128_0229cbc0;
    func_02070be8(p + 0x2cdc);
    func_ov127_0229a0e8(p + 0x4a4);
    func_020b18a8(p + 0x174);
    func_ov002_02209cb4(p + 0x110);
    func_ov002_0220b3a4(p + 0x94);
    func_ov002_0220826c(p);
    return self;
}
