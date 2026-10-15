/* func_ov002_0220b3a4 @ 0x0220b3a4, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);
extern int **func_02070be8(void *);
extern void *data_ov002_0220bd18;

void *func_ov002_0220b3a4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd18;
    func_02070b84(self + 0x4);
    func_02070be8(self + 0x4);
    return self;
}
