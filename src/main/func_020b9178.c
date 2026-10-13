/* func_020b9178 @ 0x020b9178, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e5858;
extern void func_0208a1f4(void *);
extern void func_0208ad24(void *);
extern void func_020edb3c(void *);

typedef struct {
    void *unk_00;
    char pad_04[0xCC - 4];
    void *unk_CC;
} UnkStruct_020b9178;

UnkStruct_020b9178 *func_020b9178(UnkStruct_020b9178 *self)
{
    self->unk_00 = &data_020e5858;
    func_0208a1f4(&self->unk_CC);
    func_0208ad24(self);
    func_020edb3c(self);
    return self;
}
