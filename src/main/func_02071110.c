/* func_02071110 @ 0x02071110, 0x76 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02071110 {
    char pad_00[0x60];
    unsigned char unk_60;
    unsigned char unk_61;
    unsigned char unk_62;
    unsigned char unk_63;
} UnkStruct_02071110;

extern void func_02071424(UnkStruct_02071110 *self, void *other);
extern unsigned char *func_02071318(UnkStruct_02071110 *self, void *other, int *index);
extern int func_020984d4(void);
extern int func_02070fa0(UnkStruct_02071110 *self);
extern void func_0209e474(unsigned int *data);

void func_02071110(UnkStruct_02071110 *self, void *other)
{
    int idx;
    unsigned int data[2];
    unsigned char *ptr;

    func_02071424(self, other);
    ptr = func_02071318(self, other, &idx);
    if (ptr) {
        int v = func_020984d4() & 3;
        v += 1;
        ptr[idx >> 1] |= v << ((idx & 1) << 2);
    }
    if (func_02070fa0(self)) {
        data[0] = 0;
        data[1] = 0;
        func_0209e474(data);
        self->unk_62 = ((unsigned char *) data)[5];
        self->unk_61 = ((unsigned char *) data)[4];
        self->unk_60 = ((unsigned char *) data)[3];
        self->unk_63 = 0;
    }
}
