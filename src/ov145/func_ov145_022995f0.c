/* func_ov145_022995f0 @ 0x022995f0, 0x58 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov145_0229ae00;
extern void func_02070be8(void);
extern void __cxa_vec_cleanup(void *dst, int a, int b, void (*cb)(void));
extern void func_ov002_0220afdc(void *);
extern void func_ov002_0220a5e4(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

void *func_ov145_022995f0(void *obj)
{
    *(void **) obj = &data_ov145_0229ae00;
    __cxa_vec_cleanup((char *) obj + 0x340, 0x12, 0x6c, func_02070be8);
    func_ov002_0220afdc((char *) obj + 0x174);
    func_ov002_0220a5e4((char *) obj + 0x12c);
    func_ov002_02209cb4((char *) obj + 0xc8);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}
