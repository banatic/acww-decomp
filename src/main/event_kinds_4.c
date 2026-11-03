/* event_kinds_4: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203ec3c @ 0x0203ec3c, 0x36 bytes, Thumb
 * func_0203ec34 @ 0x0203ec34, 0x8 bytes, Thumb
 * func_0203ec1c @ 0x0203ec1c, 0x18 bytes, Thumb
 * func_0203ebd0 @ 0x0203ebd0, 0x4c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x10];
    void *unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
} UnkStruct_0203ebd0;

extern int func_02070094(void);
extern int func_02095e08(void);
extern int func_02095ce0(void);
extern int func_0207004c(int);
extern int func_0206fbc0(void);
extern int func_02095bdc(void);
extern int func_0203f400(void *p);
extern int func_02095904(void);
extern void func_0203dfe4(void *p);
extern void func_0203f394(void *p);

int func_0203ec3c(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    if (func_02070094() == 0) {
        return 0;
    }
    if (func_02095e08() == 0) {
        return 0;
    }
    if (func_02095ce0() == 0) {
        return 0;
    }
    func_0207004c(*(unsigned char *) (r4 + 0x16));
    return 1;
}

void func_0203ec34(void)
{
    func_0206fbc0();
}

int func_0203ec1c(void)
{
    if (func_02095bdc() != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0203ebd0(UnkStruct_0203ebd0 *self)
{
    switch (func_0203f400(self->unk_10)) {
        case 2:
            self->unk_16 = 2;
            break;
        case 1:
            self->unk_16 = 1;
            break;
        case 0:
            return 0;
    }

    if (self->unk_15 != 7 && func_02095904() == 0) {
        return 0;
    }

    func_0203dfe4(self->unk_10);
    func_0203f394(self->unk_10);

    return 1;
}
