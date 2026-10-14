/* func_ov004_0223ed30 @ 0x0223ed30, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223eb04(void *self);
extern char data_0213efe8[];
extern char data_0213f020[];
extern void func_02032c64(void *);
extern void func_02055210(void *);
extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void func_02089b50(void *);
extern void func_0205577c(void *);
extern void func_0209d34c(void *);
extern void func_0209d11c(void *);
extern void func_0209d0a4(void *);
extern char func_020012dc[];
extern char func_020012e8[];

void *func_ov004_0223ed30(char *self)
{
    int zero;
    func_ov004_0223eb04(self);
    *(char **) (self + 0x24) = data_0213efe8;
    *(char **) (self + 0x24) = data_0213f020;
    func_02032c64(self + 0x68);
    func_02055210(self + 0xb0);
    __cxa_vec_ctor(self + 0x178, 2, 0xc, func_020012e8, func_020012dc);
    func_02089b50(self + 0x19c);
    func_0205577c(self + 0x1e8);
    func_0209d34c(self + 0x284);
    func_0209d11c(self + 0x288);
    zero = 0;
    *(signed char *) (self + 0x196) = (signed char) ~zero;
    func_0209d0a4(self + 0x288);
    *(int *) (self + 0x2d4) = 0;
    *(int *) (self + 0x198) = 0;
    return self;
}
