/* func_020ee63c @ 0x020ee63c, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edf54(void *self);
extern unsigned char data_0213e7b4;

void *func_020ee63c(void *self)
{
    *(void **) self = (void *) &data_0213e7b4;
    func_020edf54(self);
    return self;
}
