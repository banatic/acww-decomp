/* func_ov002_0220afdc @ 0x0220afdc, 0x2c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void func_ov002_0220b0f4(void *);
extern void func_ov002_0220b3a4();
extern void *data_ov002_0220bd08;

void *func_ov002_0220afdc(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd08;
    func_ov002_0220b0f4(self + 0xfc);
    __cxa_vec_cleanup(self + 0x4, 0x2, 0x7c, (void *) func_ov002_0220b3a4);
    return self;
}
