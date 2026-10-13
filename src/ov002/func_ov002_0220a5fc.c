/* func_ov002_0220a5fc @ 0x0220a5fc, 0x24 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e95c(void *, int);
extern void func_0208ec88(void *, int);
extern void *data_ov002_0220bcec;

void *func_ov002_0220a5fc(char *self)
{
    // DECLS
    // ENDDECLS
    func_0208ec88(self, 0x0);
    *(void **) (self) = &data_ov002_0220bcec;
    func_0208e95c(self, 0x0);
    return self;
}
