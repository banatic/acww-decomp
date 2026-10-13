/* func_02039750 @ 0x02039750, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *dest, int arg1, int arg2, void (*func)(void));
extern void func_020edb3c(void *self);
extern void func_0203a1f8(void);

struct UnkStruct_02039750 {
    void *unk_00;
    int unk_04;
};

extern unsigned char data_020da5d8[];

struct UnkStruct_02039750 *func_02039750(struct UnkStruct_02039750 *self)
{
    self->unk_00 = (void *) data_020da5d8;
    func_02138c48(&self->unk_04, 4, 0xb8, &func_0203a1f8);
    func_020edb3c(self);
    return self;
}
