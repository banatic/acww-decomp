/* func_ov002_0220a39c @ 0x0220a39c, 0x24 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208e7f0(void *);
extern void func_ov002_02209e38(void *);
extern void *data_ov002_0220bc88;

void *func_ov002_0220a39c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bc88;
    func_ov002_02209e38(self + 0x4c);
    func_0208e7f0(self);
    return self;
}
