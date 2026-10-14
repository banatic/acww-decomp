/* func_ov004_02245f28 @ 0x02245f28, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e84c(void *);
extern void func_02094fbc(void *);
extern void func_020ee62c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void func_0208e408();
extern void *data_020da13c;
extern void *data_ov004_0225684c;

void *func_ov004_02245f28(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_0225684c;
    func_02094fbc(self + 0x338);
    __cxa_vec_cleanup(self + 0x9c, 0x5, 0x80, (void *) func_0208e408);
    func_0208e84c(self + 0x50);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}
