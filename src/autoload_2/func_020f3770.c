/* func_020f3770 @ 0x020f3770, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f4514(void *);
extern unsigned char data_0213ead4;

void *func_020f3770(void *self)
{
    *(void **) self = (void *) &data_0213ead4;
    func_020f4514(self);
    return self;
}
