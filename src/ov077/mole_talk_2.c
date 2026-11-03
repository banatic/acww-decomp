/* mole_talk_2: 5 functions, module ov077
 * mwccarm 1.2/base -O4,s
 * func_ov077_02278d64 @ 0x02278d64, 0x18 bytes, Thumb
 * func_ov077_02278d4c @ 0x02278d4c, 0x18 bytes, Thumb
 * func_ov077_02278d2c @ 0x02278d2c, 0x20 bytes, Thumb
 * func_ov077_02278d00 @ 0x02278d00, 0x2a bytes, Thumb
 * func_ov077_02278cbc @ 0x02278cbc, 0x42 bytes, Thumb
 */

typedef struct UnkStruct_02278d00 {
    char pad_00[0xBC];
    unsigned char unk_BC;
} UnkStruct_02278d00;

struct UnkStruct_02278cbc {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
};

extern void *func_0202eb70(void *);
extern char data_ov077_022797fc;
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *self);
extern void func_02035624(int);
extern void func_020356c4(int, int, int, int);
extern void func_02035638(int);
extern void func_02035684(int, int, int);

void *func_ov077_02278d64(void *p)
{
    func_0202eb70(p);
    *(void **) p = &data_ov077_022797fc;
    return p;
}

void *func_ov077_02278d4c(void *self)
{
    *(void **) self = &data_ov077_022797fc;
    func_0202eb20(self);
    return self;
}

void *func_ov077_02278d2c(void *self)
{
    *(unsigned int *) self = (unsigned int) ((unsigned int *) &data_ov077_022797fc);
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}

void func_ov077_02278d00(UnkStruct_02278d00 *self)
{
    if (self->unk_BC == 0) {
        func_02035624(0x17);
        func_020356c4(0x18, 0x43, 0x7f, 1);
        self->unk_BC = 1;
    }
}

void func_ov077_02278cbc(struct UnkStruct_02278cbc *p)
{
    switch (p->unk_1E) {
        case 3:
        case 8:
        case 18:
        case 26:
        case 35:
            func_02035638(0x43);
            func_02035684(0x17, 0x16, 0x20);
            break;
        default:
            break;
    }
}
