/* func_ov143_022995a0 @ 0x022995a0, 0x44 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220826c(void *);
extern void func_02070be8(void);
extern int data_ov143_0229b1c0;

void *func_ov143_022995a0(void *this)
{
    *(void **) this = (void *) &data_ov143_0229b1c0;
    __cxa_vec_cleanup((char *) this + 0x2dc, 0x10, 0x6c, &func_02070be8);
    func_ov002_0220afdc((char *) this + 0x110);
    func_ov002_02209cb4((char *) this + 0xac);
    func_ov002_0220826c(this);
    return this;
}
