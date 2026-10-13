/* func_ov004_02245f70 @ 0x02245f70, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e878(void *, int);
extern void func_02094fd4(void *);
extern void func_020ee660(void *);
extern void func_02138d6c(void *, int, int, void *, void *);
extern void func_0208e408();
extern void func_0208e438();
extern void *data_020da13c;
extern void *data_ov004_0225684c;

void *func_ov004_02245f70(char *self)
{
    // DECLS
    // ENDDECLS
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_0225684c;
    func_0208e878(self + 0x50, 0x1);
    func_02138d6c(self + 0x9c, 0x5, 0x80, (void *) func_0208e438, (void *) func_0208e408);
    *(void **) (self + 0x328) = 0x0;
    *(void **) (self + 0x32c) = 0x0;
    func_02094fd4(self + 0x338);
    return self;
}
