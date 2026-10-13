/* func_020ea388 @ 0x020ea388, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea3ac(void *self);
extern char data_0213e5b0;

void *func_020ea388(void *self)
{
    *(void **) self = &data_0213e5b0;
    func_020ea3ac(self);
    return self;
}
