/* func_020bd2d0 @ 0x020bd2d0, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, will be removed

typedef struct UnkStruct_020bd2d0 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
} UnkStruct_020bd2d0;

extern UnkStruct_020bd2d0 *data_020ccf94;

typedef struct UnkStruct_020bd2d0_2 {
    unsigned char pad_00[0x1464];
    unsigned int unk_1464;
    unsigned char pad_1468[0x2eb8 - 0x1468];
    unsigned char pad_2EB8[0x2f18 - 0x2eb8];
    unsigned char unk_2F18;
    unsigned char unk_2F19;
    unsigned char unk_2F1A;
    unsigned char pad_2F1B[0x2f24 - 0x2f1b];
    unsigned char unk_2F24;
} UnkStruct_020bd2d0_2;

extern int func_02073dd4(UnkStruct_020bd2d0 *a, unsigned int b);
extern int func_020644cc(int a);
extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_020be9dc(void);
extern void *func_020bdc50(void *a, int b, int c, int d, int e);
extern void func_020bece0(void *a);

void func_020bd2d0(UnkStruct_020bd2d0_2 *self)
{
    int r0, r5;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }
    if (self->unk_2F19 < 10 || self->unk_2F19 >= 16) {
        return;
    }
    if (self->unk_2F1A == self->unk_2F18) {
        return;
    }
    if ((unsigned int) self->unk_2F18 % 10 != 4) {
        return;
    }
    if (self->unk_1464 == 5) {
        return;
    }
    if (self->unk_2F24 == 0) {
        self->unk_2F24 = func_020644cc(8) + 1;
    }
    r5 = self->unk_2F24;
    r0 = func_020644cc(8);
    if (r0 < r5) {
        if (func_02099020(func_020984e8(), 0x30) == 0 && func_020be9dc() != 0 && func_020644cc(4) == 0) {
            func_020bdc50(self, 5, 0x2d, 0, 1);
        } else {
            func_020bdc50(self, 5, 0x2d, 0, 0);
            func_020bece0((char *) self + 0x2eb8);
        }
        self->unk_2F24 = 1;
    } else {
        if ((unsigned int) r5 < 8) {
            self->unk_2F24 = self->unk_2F24 + 1;
        }
    }
}