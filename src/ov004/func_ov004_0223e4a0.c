/* func_ov004_0223e4a0 @ 0x0223e4a0, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02032c50(void *);
extern void *func_020551e0(void *);
extern void *func_02089bbc(void *);
extern int func_020e8ce0(void *, void *);
extern void func_020ee62c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void func_020012dc(void *arg0);
extern void *data_020d7244;
extern void *data_020da13c;
extern void *data_0213ff78;
extern void *data_ov004_0225622c;

void *func_ov004_0223e4a0(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0225622c;
    __cxa_vec_cleanup(self + 0x248, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    __cxa_vec_cleanup(self + 0x230, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    func_02089bbc(self + 0x1d8);
    func_020551e0(self + 0x120);
    func_02032c50(self + 0xdc);
    *(void **) (self) = &data_020d7244;
    func_020e8ce0(&data_0213ff78, self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}
