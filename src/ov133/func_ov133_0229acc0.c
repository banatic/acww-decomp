/* func_ov133_0229acc0 @ 0x0229acc0, 0x50 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov133_0229c908;
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_02209cb4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_02070be8(void);
extern void func_ov002_0220826c(void *);

void *func_ov133_0229acc0(void *obj)
{
    *(void **) obj = &data_ov133_0229c908;
    func_ov002_0220ba0c((char *) obj + 0x1394);
    func_ov002_0220afdc((char *) obj + 0x180);
    func_ov002_02209cb4((char *) obj + 0x11c);
    __cxa_vec_cleanup((char *) obj + 0xb0, 1, 0x6c, func_02070be8);
    func_ov002_0220826c(obj);
    return obj;
}
