/* func_0208def4 @ 0x0208def4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e226c;
extern void *func_0208a144(void *);
extern void func_0208dd60(void *);
extern void *func_0208e00c(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

typedef struct {
    int *unk_00;
    char pad_04[8];
    int unk_0C;
    char pad_10[0x58];
    int unk_68;
    char pad_6C[0x18];
    int unk_84;
    char pad_88[0x18];
    int unk_A0;
    char pad_A4[0x18];
    int unk_BC;
} UnkStruct_0208def4;

void *func_0208def4(UnkStruct_0208def4 *self)
{
    self->unk_00 = &data_020e226c;
    func_0208a144(&self->unk_0C);
    func_0208dd60(self);
    func_0208e00c(&self->unk_BC);
    func_0208e00c(&self->unk_A0);
    func_0208e00c(&self->unk_84);
    func_0208e00c(&self->unk_68);
    func_0208a1f4(&self->unk_0C);
    func_0208af00(self);
    return self;
}
