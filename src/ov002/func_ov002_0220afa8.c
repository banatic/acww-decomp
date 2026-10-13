/* func_ov002_0220afa8 @ 0x0220afa8, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *);
extern void func_02138c48(void *, int, int, void *);
extern void func_ov002_0220b0f4(void *);
extern void func_ov002_0220b3a4();
extern void *data_ov002_0220bd08;

void *func_ov002_0220afa8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd08;
    func_ov002_0220b0f4(self + 0xfc);
    func_02138c48(self + 0x4, 0x2, 0x7c, (void *) func_ov002_0220b3a4);
    func_020edb3c(self);
    return self;
}
