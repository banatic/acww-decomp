/* func_020f3858 @ 0x020f3858, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *);
extern unsigned char data_0213eaa0[];

void *func_020f3858(void *self)
{
    func_020f45c4(self);
    *(void **) self = (void *) data_0213eaa0;
    *(unsigned char *) ((char *) self + 4) = 0x15;
    return self;
}
