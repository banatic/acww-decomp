/* func_020370cc @ 0x020370cc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da324;
extern void func_020edb3c(void *);

void *func_020370cc(void *self)
{
    *(void **) self = &data_020da324;
    func_020edb3c(self);
    return self;
}
