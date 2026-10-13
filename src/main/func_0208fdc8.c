/* func_0208fdc8 @ 0x0208fdc8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *a, void *b);
extern void func_0208a1ec(void *a, int b);
extern void func_0208a144(void *a);
extern char data_020d6fcc[];

typedef struct {
    char pad_00[12];
    int unk_0C;
    char pad_10[4];
    char unk_14[20];
    char unk_28;
} UnkStruct_0208fdc8;

void func_0208fdc8(UnkStruct_0208fdc8 *self)
{
    int field_c = self->unk_0C;
    if (field_c == 0) {
        self->unk_28 = 0;
        return;
    }
    {
        int code = (field_c == 1) ? 0x43 : 0x44;
        func_0208a1f0(&self->unk_14, data_020d6fcc + (code << 3));
        func_0208a1ec(&self->unk_14, 1);
        func_0208a144(&self->unk_14);
        self->unk_28 = 1;
    }
}
