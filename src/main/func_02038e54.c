/* func_02038e54 @ 0x02038e54, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02039304(void *);
extern void func_0203977c(void *);
extern void func_0203909c(void *);
extern void func_020ee62c(void *);

struct obj {
    void *vtable;
};

extern unsigned char data_020da13c[];
extern unsigned char data_020da674[];

void *func_02038e54(void *self)
{
    char *p;
    struct obj *o = (struct obj *) self;
    o->vtable = (void *) data_020da674;
    func_02039304((char *) self + 0x358);
    p = (char *) self;
    p += 0x54;
    func_0203977c(p);
    p = (char *) self;
    p += 0x50;
    func_0203909c(p);
    o->vtable = (void *) data_020da13c;
    func_020ee62c(self);
    return self;
}
