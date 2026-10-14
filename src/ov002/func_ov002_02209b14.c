/* func_ov002_02209b14 @ 0x02209b14, 0x58 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void func_ov002_022087d4(void *);
extern void func_ov002_0220b10c(void *);
extern void func_ov002_0220b47c(void *);
extern void func_ov002_02209bf0();
extern void func_ov002_02209c08();
extern void *data_ov002_0220bb98;

void *func_ov002_02209b14(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bb98;
    __cxa_vec_ctor(self + 0x28, 0x5, 0x74, (void *) func_ov002_02209c08, (void *) func_ov002_02209bf0);
    func_ov002_0220b47c(self + 0x26c);
    func_ov002_0220b10c(self + 0x2e4);
    func_ov002_022087d4(self + 0x3b0);
    return self;
}
