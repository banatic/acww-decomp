/* func_0208b5b0 @ 0x0208b5b0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e21d4;
extern void *func_0208bb8c(void *p);
extern void *func_0208c1ac(void *p);
extern void *func_0208d2e8(void *p);
extern void *func_0208def4(void *p);

struct BigStruct {
    void *unk_00;
    char pad_04[4];
    char sub_8;
    char pad_09[0xe0 - 9];
    char sub_e0;
    char pad_E1[0x1c4 - (0xe0 + 1)];
    char sub_1c4;
    char pad_1C5[0x2c4 - (0x1c4 + 1)];
    char sub_2c4;
};

struct BigStruct *func_0208b5b0(struct BigStruct *self)
{
    self->unk_00 = (void *) &data_020e21d4;
    func_0208bb8c(&self->sub_2c4);
    func_0208c1ac(&self->sub_1c4);
    func_0208d2e8(&self->sub_e0);
    func_0208def4(&self->sub_8);
    return self;
}
