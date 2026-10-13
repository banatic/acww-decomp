/* func_ov004_0223e418 @ 0x0223e418, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02032c50(void *);
extern void func_020551e0(void *);
extern void func_02089bbc(void *);
extern void func_020e8ce0(void *, void *);
extern void func_020edf54(void *);
extern void func_020ee62c(void *);
extern void func_02138c48(void *, int, int, void *);
extern void func_020012dc();
extern void *data_020d7244;
extern void *data_020da13c;
extern void *data_0213ff78;
extern void *data_ov004_0225622c;

void *func_ov004_0223e418(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0225622c;
    func_02138c48(self + 0x248, 0x2, 0xc, (void *) func_020012dc);
    func_02138c48(self + 0x230, 0x2, 0xc, (void *) func_020012dc);
    func_02089bbc(self + 0x1d8);
    func_020551e0(self + 0x120);
    func_02032c50(self + 0xdc);
    *(void **) (self) = &data_020d7244;
    func_020e8ce0(&data_0213ff78, self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
