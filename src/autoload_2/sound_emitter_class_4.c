/* sound_emitter_class_4: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f5a10 @ 0x020f5a10, 0x2c bytes, ARM
 * func_020f59ec @ 0x020f59ec, 0x24 bytes, ARM
 */

extern char data_0213f090[];
extern void func_020f5914(void *);
extern void func_020edb3c(void *);

void *func_020f5a10(void *self)
{
    *(void **) self = data_0213f090;
    func_020f5914(self);
    func_020edb3c(self);
    return self;
}

void *func_020f59ec(void *self)
{
    *(void **) self = ((char *) data_0213f090);
    func_020f5914(self);
    return self;
}
