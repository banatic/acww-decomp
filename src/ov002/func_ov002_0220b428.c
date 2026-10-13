/* func_ov002_0220b428 @ 0x0220b428, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b698(void *, int, int);
extern void *data_ov002_0220bd58;

void *func_ov002_0220b428(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov002_0220b698(self, 0x1, 0x0);
    *(void **) (self) = &data_ov002_0220bd58;
    return self;
}
