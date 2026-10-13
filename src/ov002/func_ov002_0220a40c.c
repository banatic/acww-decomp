/* func_ov002_0220a40c @ 0x0220a40c, 0x3c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e508(void *, int);
extern void func_0208e5cc(void *);
extern void func_0208e8d4(void *);
extern void func_ov002_02209e18(void *);
extern void func_ov002_02209e44(void *);
extern void *data_ov002_0220bc88;

void *func_ov002_0220a40c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0208e8d4(self);
    *(void **) (self) = &data_ov002_0220bc88;
    func_ov002_02209e44(self + 0x4c);
    func_0208e508(self, 0x0);
    func_ov002_02209e18(self + 0x4c);
    *(void **) (self + 0x28) = 0x0;
    func_0208e5cc(self);
    return self;
}
