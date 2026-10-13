/* func_020c2c5c @ 0x020c2c5c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e7ea4;
extern void func_020c338c(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);

void *func_020c2c5c(void *self)
{
    *(void **) self = &data_020e7ea4;
    func_020c338c((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
