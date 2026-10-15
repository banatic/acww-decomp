/* func_ov009_0226539c @ 0x0226539c, 0x60 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov009_022658dc;
extern int data_ov009_022659a0;
extern void func_0209d340(void *);
extern void *func_ov009_02262f74(void *);
extern void *func_020b33b8(void *);
extern void *func_020551e0(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);

void *func_ov009_0226539c(void *self)
{
    *(void **) self = &data_ov009_022658dc;
    *(void **) ((char *) self + 0xec) = &data_ov009_022659a0;
    func_0209d340((char *) self + 0x292);
    func_ov009_02262f74((char *) self + 0x238);
    func_020b33b8((char *) self + 0x1f4);
    func_020551e0((char *) self + 0x13c);
    func_02066994((char *) self + 0xec);
    func_0203f080(self);
    return self;
}
