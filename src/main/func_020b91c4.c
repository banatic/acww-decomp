/* func_020b91c4 @ 0x020b91c4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208ade8(void *self, int flag);
extern void func_0208a1f8(void *sub);
extern char data_020e5858;

typedef struct {
    void *ptr;
    char pad_04[0xc8];
    char sub[20];
    int unk_E0;
    char unk_E4;
    char unk_E5;
    char unk_E6;
    char unk_E7;
    char unk_E8;
} UnkStruct_020b91c4;

void *func_020b91c4(UnkStruct_020b91c4 *self)
{
    func_0208ade8(self, 1);
    self->ptr = &data_020e5858;
    func_0208a1f8(self->sub);
    self->unk_E0 = 0;
    self->unk_E4 = 0;
    self->unk_E5 = 0;
    self->unk_E6 = 0;
    self->unk_E7 = 0;
    self->unk_E8 = 0;
    return self;
}
