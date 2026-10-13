/* func_ov002_0220b10c @ 0x0220b10c, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208aa88(void *);
extern void func_0208ade8(void *, int);
extern void *data_ov002_0220bdac;

void *func_ov002_0220b10c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0208ade8(self, 0x0);
    *(void **) (self) = &data_ov002_0220bdac;
    func_0208aa88(self);
    return self;
}
