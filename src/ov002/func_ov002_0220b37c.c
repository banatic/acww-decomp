/* func_ov002_0220b37c @ 0x0220b37c, 0x28 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);
extern void func_02070be8(void *);
extern void func_020edb3c(void *);
extern void *data_ov002_0220bd18;

void *func_ov002_0220b37c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd18;
    func_02070b84(self + 0x4);
    func_02070be8(self + 0x4);
    func_020edb3c(self);
    return self;
}
