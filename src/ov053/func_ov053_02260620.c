/* func_ov053_02260620 @ 0x02260620, 0xfc bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02260620_2 UnkStruct_02260620_2;
typedef void (*SubFn)(UnkStruct_02260620_2 *);

typedef struct SubVtbl {
    unsigned char pad_00[8];
    SubFn fn;
} SubVtbl;

struct UnkStruct_02260620_2 {
    SubVtbl *vtbl;
};

typedef struct UnkStruct_02260620 {
    unsigned char pad_00[0x560];
    unsigned char unk_560;
    unsigned char pad_561[0x658 - 0x561];
    UnkStruct_02260620_2 sub;
} UnkStruct_02260620;

extern int func_020984e8(void);
extern void *func_0201c2a4(UnkStruct_02260620 *self, int r);
extern void func_02016108(UnkStruct_02260620_2 *sub, void *res);
extern int func_ov053_02260ba8(UnkStruct_02260620_2 *sub);
extern void func_ov053_02260bb0(UnkStruct_02260620_2 *sub, int r);
extern void func_ov053_02261524(UnkStruct_02260620 *self, int r);

void func_ov053_02260620(UnkStruct_02260620 *self, unsigned int mode, unsigned char val)
{
    void *res;

    func_020984e8();
    self->unk_560 = val;

    switch (mode) {
        case 3:
            func_ov053_02261524(self, 10);
            break;

        case 1:
            self->unk_560 = val;
            self->sub.vtbl->fn(&self->sub);
            res = func_0201c2a4(self, 4);
            func_02016108(&self->sub, res);
            if (func_ov053_02260ba8(&self->sub) == 4 || func_ov053_02260ba8(&self->sub) == 3) {
                func_ov053_02261524(self, 6);
            } else {
                func_ov053_02261524(self, 2);
            }
            break;

        case 0:
            self->sub.vtbl->fn(&self->sub);
            res = func_0201c2a4(self, 4);
            func_02016108(&self->sub, res);
            func_ov053_02261524(self, 2);
            break;

        case 8:
            if (func_ov053_02260ba8(&self->sub) == 9) {
                func_ov053_02260bb0(&self->sub, 14);
                func_ov053_02261524(self, 5);
            } else {
                if (func_ov053_02260ba8(&self->sub) != 10) {
                    func_ov053_02260bb0(&self->sub, 14);
                    func_ov053_02261524(self, 4);
                }
            }
            break;

        default:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
    }
}
