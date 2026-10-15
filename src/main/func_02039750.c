/* func_02039750 @ 0x02039750, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020edb3c(void *self);
extern void *func_0203a1f8(void *);

struct UnkStruct_02039750 {
    void *unk_00;
    int unk_04;
};

extern unsigned char data_020da5d8[];

struct UnkStruct_02039750 *func_02039750(struct UnkStruct_02039750 *self)
{
    self->unk_00 = (void *) data_020da5d8;
    __cxa_vec_cleanup((void *) (&self->unk_04), 4, 0xb8, (((void (*)(void *)) func_0203a1f8)));
    func_020edb3c(self);
    return self;
}
