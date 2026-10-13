/* func_020f326c @ 0x020f326c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213ec0c;
extern void func_020f4514(void *);
extern void func_020edb3c(void *);

void *func_020f326c(void *self)
{
    *(void **) self = &data_0213ec0c;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
