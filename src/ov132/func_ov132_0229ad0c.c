/* func_ov132_0229ad0c @ 0x0229ad0c, 0x54 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov132_0229b990;
extern void func_ov002_0220ba0c(void *p);
extern void __cxa_vec_cleanup(void *p, int a, int b, unsigned int c);
extern void func_ov002_0220afdc(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);

extern void func_02070be8(void);

void *func_ov132_0229ad0c(void *obj)
{
    *(int *) obj = (int) &data_ov132_0229b990;
    func_ov002_0220ba0c((char *) obj + 0x3e4);
    __cxa_vec_cleanup((char *) obj + 0x2c4, 2, 0x6c, (unsigned int) func_02070be8);
    func_ov002_0220afdc((char *) obj + 0xf8);
    func_ov002_02209cb4((char *) obj + 0x94);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}
