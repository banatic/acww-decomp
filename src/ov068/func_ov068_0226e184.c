/* func_ov068_0226e184 @ 0x0226e184, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov068_0226e5d4(void *p);
extern void *func_0202ee5c(void *p);
extern char data_ov068_02277574;

void *func_ov068_0226e184(void *self)
{
    *(void **) self = (void *) &data_ov068_02277574;
    func_ov068_0226e5d4((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
