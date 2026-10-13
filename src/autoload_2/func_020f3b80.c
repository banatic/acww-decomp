/* func_020f3b80 @ 0x020f3b80, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ea04;
extern void func_020f9868(void *p);
extern void func_020f4514(void *p);
extern void func_020edb3c(void *p);

void *func_020f3b80(void *self)
{
    *(void **) self = (void *) &data_0213ea04;
    func_020f9868((char *) self + 8);
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
