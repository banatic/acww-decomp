/* func_02065fc4 @ 0x02065fc4, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066650(void *p);
extern void func_02065eac(void *p, int x);
extern void func_020666b0(void *p, int y);
extern void func_020666b4(void *p);
extern void func_020663d4(void *p, int *d, int a, int b, int c);

typedef struct {
    char pad_00[4];
    unsigned char unk_04[0x20];
    unsigned char unk_24[0xD5];
    unsigned char unk_F9;
    unsigned char pad_FA;
    unsigned char unk_FB;
} UnkStruct_02065fc4;

void func_02065fc4(UnkStruct_02065fc4 *self, int a, int b, int c, int d)
{
    func_02066650(self);
    self->unk_F9 = 0xc;
    func_02065eac(self, 5);
    func_020666b0(&self->unk_24, 4);
    func_020666b4(&self->unk_04);
    if (d < 0) {
        func_020666b0(&self->unk_04, 6);
        d = 0;
    }
    self->unk_FB = 0xc;
    func_020663d4(self, &d, a, b, c);
}
