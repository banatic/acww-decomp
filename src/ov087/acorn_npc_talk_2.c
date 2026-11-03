/* acorn_npc_talk_2: 3 functions, module ov087
 * mwccarm 1.2/base -O4,s
 * func_ov087_02278ff4 @ 0x02278ff4, 0x18 bytes, Thumb
 * func_ov087_02278fdc @ 0x02278fdc, 0x18 bytes, Thumb
 * func_ov087_02278fbc @ 0x02278fbc, 0x20 bytes, Thumb
 */

extern void *func_0202eb70(void *p);
extern char data_ov087_0227945c;
extern void *func_0202eb20(void *obj);
extern void func_020edb3c(void *self);

void *func_ov087_02278ff4(void *arg)
{
    func_0202eb70(arg);
    *(void **) arg = (void *) &data_ov087_0227945c;
    return arg;
}

void *func_ov087_02278fdc(void *obj)
{
    *(void **) obj = (void *) &data_ov087_0227945c;
    func_0202eb20(obj);
    return obj;
}

void *func_ov087_02278fbc(void *self)
{
    *(void **) self = (void *) &data_ov087_0227945c;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
