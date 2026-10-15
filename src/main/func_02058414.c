/* func_02058414 @ 0x02058414, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9390[3];
extern void func_0205967c(void *a, void *b);
extern void func_02059674(void *a, int b);
extern void func_020ea6e0(void *a, int b);
extern void VEC_Add(void *a, void *b, void *c);
typedef struct {
    char pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    int unk_78[3];
    char pad_84[0x90 - 0x84];
    int unk_90;
    int unk_94;
    int unk_98;
    char pad_9C[0xcc - 0x9c];
    void *unk_CC;
    char pad_D0[0xd6 - 0xd0];
    short unk_D6;
} UnkStruct_02058414;
void func_02058414(UnkStruct_02058414 *self)
{
    int d1;
    int d0;
    int d2;
    func_0205967c(self, ((char *) self) + 0x6c);
    if (self->unk_CC) {
        self->unk_78[0] = data_021c9390[0];
        self->unk_78[1] = data_021c9390[1];
        self->unk_78[2] = data_021c9390[2];
        func_020ea6e0(self->unk_78, *((short *) (((char *) self->unk_CC) + 0x8e)));
    }
    VEC_Add(((char *) self) + 0x6c, ((char *) self) + 0x78, ((char *) self) + 0x6c);
    d0 = (self->unk_74 - self->unk_68) / 2;
    if (d0 < 0) {
        d0 = -d0;
    }
    d1 = (self->unk_70 - self->unk_64) / 2;
    if (d1 < 0) {
        d1 = -d1;
    }
    d2 = (self->unk_6C - self->unk_60) / 2;
    if (d2 < 0) {
        d2 = -d2;
    }
    self->unk_90 = d2;
    self->unk_94 = d1;
    self->unk_98 = d0;
    self->unk_D6 = 0;
    func_02059674(self, 1);
}
