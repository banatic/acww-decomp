/* func_020834c8 @ 0x020834c8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083ca8(void *self, int b);
extern void func_02083514(void);
extern void func_0208352c(void);
extern char data_020e1a90;
extern void __cxa_vec_ctor(void *ptr, int a, int b, void (*cb1)(void), void (*cb2)(void));

struct UnkStruct_020834c8 {
    void *unk_00;
    void *unk_04;
    char unk_08;
};

struct UnkStruct_020834c8 *func_020834c8(struct UnkStruct_020834c8 *self)
{
    func_02083ca8(self, 5);
    self->unk_00 = &data_020e1a90;
    __cxa_vec_ctor(&self->unk_08, 5, 2, func_0208352c, func_02083514);
    return self;
}
