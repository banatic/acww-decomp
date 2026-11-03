/* outdoor_villager: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226682c @ 0x0226682c, 0x50 bytes, Thumb
 * func_ov068_022667e0 @ 0x022667e0, 0x4c bytes, Thumb
 */

extern void func_ov068_02266f3c(void *);
extern void *func_02012588(void *);
extern void *func_ov068_0226ce48(void *);
extern void func_ov068_02266cec(void *);
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);
extern unsigned char data_ov068_022771c0[];

void *func_ov068_0226682c(void *self)
{
    *(void **) self = (void *) data_ov068_022771c0;
    func_ov068_02266f3c((char *) self + 0x9f4);
    func_02012588((char *) self + 0x9b4);
    func_ov068_0226ce48((char *) self + 0x8b8);
    func_ov068_02266cec((char *) self + 0x898);
    func_0202e5e0(self);
    func_020edf54(self);
    return self;
}

void *func_ov068_022667e0(void *param)
{
    *(unsigned int *) param = (unsigned int) ((unsigned char *) data_ov068_022771c0);
    func_ov068_02266f3c((char *) param + 0x9f4);
    func_02012588((char *) param + 0x9b4);
    func_ov068_0226ce48((char *) param + 0x8b8);
    func_ov068_02266cec((char *) param + 0x898);
    func_0202e5e0(param);
    return param;
}
