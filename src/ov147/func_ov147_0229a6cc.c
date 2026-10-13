/* func_ov147_0229a6cc @ 0x0229a6cc, 0x18 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *p);
extern char data_ov147_0229ac1c;

void *func_ov147_0229a6cc(void *self)
{
    *(void **) self = &data_ov147_0229ac1c;
    func_020edb3c(self);
    return self;
}
