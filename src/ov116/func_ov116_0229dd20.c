/* func_ov116_0229dd20 @ 0x0229dd20, 0x40 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *dst, int a, int b, void (*func)(void));
extern void func_ov114_0229d9d8(void *ptr);
extern void func_ov002_02209cb4(void *ptr);
extern void func_ov002_0220826c(void *ptr);
extern void func_02070be8(void);
extern char data_ov116_0229e8b8;

void *func_ov116_0229dd20(void *obj)
{
    *(unsigned int *) obj = (unsigned int) &data_ov116_0229e8b8;
    __cxa_vec_cleanup((char *) obj + 0x13b8, 1, 0x6c, func_02070be8);
    func_ov114_0229d9d8((char *) obj + 0xf8);
    func_ov002_02209cb4((char *) obj + 0x94);
    func_ov002_0220826c(obj);
    return obj;
}
