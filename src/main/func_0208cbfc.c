/* func_0208cbfc @ 0x0208cbfc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x34 - 0x28];
    char unk_34;
    char pad_35[0xa4 - 0x35];
    unsigned char flag_a4;
    char pad_A5[0xc1 - 0xa5];
    unsigned char unk_C1;
} UnkStruct_0208cbfc;

extern void func_020b45d0(void *a, unsigned char b, int c, int d, int e, int f);
extern void func_02051624(void *p);
extern void func_02051694(void *p);

void func_0208cbfc(UnkStruct_0208cbfc *self)
{
    if (self->flag_a4 == 0) {
        return;
    }
    if (self->unk_24 == 0) {
        return;
    }
    func_020b45d0(&self->unk_34, self->unk_C1, 2, 6, 0, 1);
    func_02051624(self->unk_24);
    func_02051694(self->unk_24);
    self->flag_a4 = 0;
}
