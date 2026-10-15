/* func_0208cb70 @ 0x0208cb70, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
    char pad_30[0x6c - 0x30];
    char unk_6C[0xa6 - 0x6c];
    unsigned char flag_a6;
    char pad_A7[0xac - 0xa7];
    void *unk_AC;
} UnkStruct_0208cb70;

extern int func_020b45d0(void *a, void *b, int c, int d, int e, int f);
extern void func_02051648(void *a);
extern void func_02051694(void *a);

void func_0208cb70(UnkStruct_0208cb70 *self)
{
    if (self->flag_a6 != 0 && self->unk_2C != 0) {
        func_020b45d0(self->unk_6C, self->unk_AC, 2, 6, 0, 1);
        func_02051648(self->unk_2C);
        func_02051694(self->unk_2C);
        self->flag_a6 = 0;
    }
}
