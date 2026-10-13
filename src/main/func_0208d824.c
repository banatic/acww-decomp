/* func_0208d824 @ 0x0208d824, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x4f - 0x44];
    unsigned char unk_4F;
} SELF;

typedef struct {
    unsigned char pad_00[0x10];
    int *unk_10;
    unsigned char pad_14[0x28 - 0x14];
    int *unk_28;
    int unk_2C;
    unsigned char pad_30[0x38 - 0x30];
    unsigned char unk_38;
    unsigned char unk_39;
    unsigned char pad_3A[0x50 - 0x3a];
    int unk_50;
    unsigned char pad_54[0x55 - 0x54];
    unsigned char unk_55;
} OBJ;

extern void *func_020a9034(int size, int a, int b);
extern void func_02051648(OBJ *obj);
extern void func_0205166c(OBJ *obj, int a);
extern int data_020d0a54;
extern int data_021c82e8;

void func_0208d824(SELF *self)
{
    if (self->unk_40 != 0) {
        return;
    }
    self->unk_40 = func_020a9034(self->unk_4F ? 0xd8 : 0x8c, 1, 2);
    if (self->unk_40 == 0) {
        return;
    }
    ((OBJ *) self->unk_40)->unk_2C = 4;
    ((OBJ *) self->unk_40)->unk_10 = &data_020d0a54;
    ((OBJ *) self->unk_40)->unk_50 = 2;
    ((OBJ *) self->unk_40)->unk_55 = 1;
    ((OBJ *) self->unk_40)->unk_28 = &data_021c82e8;
    func_02051648((OBJ *) self->unk_40);
    ((OBJ *) self->unk_40)->unk_39 = 0;
    ((OBJ *) self->unk_40)->unk_38 = 9;
    func_0205166c((OBJ *) self->unk_40, 0);
}