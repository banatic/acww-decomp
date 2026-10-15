/* func_ov002_02207e28 @ 0x02207e28, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208ad24(void *a);
extern char data_ov002_0220baa8;

void *func_ov002_02207e28(void *self)
{
    *(void **) self = (void *) &data_ov002_0220baa8;
    func_0208ad24(self);
    return self;
}
