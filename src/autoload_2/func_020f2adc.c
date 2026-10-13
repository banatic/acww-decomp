/* func_020f2adc @ 0x020f2adc, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f2adc {
    void *vtbl;
};

extern char data_0213ede0;
extern void func_020f4514(struct UnkStruct_020f2adc *);
extern void func_020edb3c(struct UnkStruct_020f2adc *);

struct UnkStruct_020f2adc *func_020f2adc(struct UnkStruct_020f2adc *self)
{
    self->vtbl = &data_0213ede0;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
