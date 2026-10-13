/* func_ov122_0229fedc @ 0x0229fedc, 0x50 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229efd8(void *p, int n);
extern void func_ov122_0229f590(void *p, int n);
extern void func_ov122_0229f940(void *p);
extern void func_ov122_022a14c0(void *p);
extern void func_ov095_0229cd30(void *p);

void func_ov122_0229fedc(void *self)
{
    func_ov122_0229efd8(self, 4);
    *(int *) ((char *) self + 0x9c) = 0x30;
    *(int *) ((char *) self + 0xa0) = 0x40;
    *(unsigned char *) ((char *) self + 0xaa) = 2;
    func_ov122_0229efd8(self, 0x1000);
    func_ov122_0229f590(self, 0);
    func_ov122_0229f940(self);
    func_ov095_0229cd30((char *) self + 0xc0);
    func_ov122_022a14c0(self);
}
