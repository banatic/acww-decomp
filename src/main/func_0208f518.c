/* func_0208f518 @ 0x0208f518, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Struct0208F518 {
    void *unk_00;
    char pad_04[8];
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    char sub_1c[20];
    char sub_30[20];
    int unk_44;
    int unk_48;
    char sub_4c[36];
    unsigned short unk_70;
    unsigned char unk_72;
    unsigned char unk_73;
    unsigned char unk_74;
    unsigned char unk_75;
} Struct0208F518;

extern void func_0208af30(void *self, int param1, int param2);
extern void func_0208a1f8(char *data);
extern void func_0208f640(char *data);
extern void func_0208f0c4(void *self);

extern unsigned char data_020e23a0[];

Struct0208F518 *func_0208f518(Struct0208F518 *self, int param1, int param2)
{
    func_0208af30(self, param1, param2);
    self->unk_00 = (void *) data_020e23a0;
    self->unk_0C = 0;
    self->unk_10 = 0;
    self->unk_14 = -1;
    self->unk_18 = param2;
    func_0208a1f8(self->sub_1c);
    func_0208a1f8(self->sub_30);
    self->unk_44 = 0;
    self->unk_48 = 0;
    func_0208f640(self->sub_4c);
    self->unk_70 = 0x50c0;
    self->unk_72 = (unsigned char) param1;
    self->unk_73 = 0;
    self->unk_74 = 0;
    self->unk_75 = 0;
    func_0208f0c4(self);
    return self;
}
