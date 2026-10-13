/* func_0203ebd0 @ 0x0203ebd0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203f400(void *p);
extern int func_02095904(void);
extern void func_0203dfe4(void *p);
extern void func_0203f394(void *p);

typedef struct {
    unsigned char pad_00[0x10];
    void *unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
} UnkStruct_0203ebd0;

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
