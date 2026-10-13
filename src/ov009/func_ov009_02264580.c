/* func_ov009_02264580 @ 0x02264580, 0x38 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02264580 {
    char pad_00[0x1c];
    unsigned int unk_1C;
} UnkStruct_02264580;

typedef struct UnkStruct_02264580_2 {
    char pad_00[0x284];
    unsigned int unk_284;
} UnkStruct_02264580_2;

extern UnkStruct_02264580 *func_ov009_02264884(UnkStruct_02264580_2 *self);
extern unsigned int func_ov009_02264394(unsigned int v);

void func_ov009_02264580(UnkStruct_02264580_2 *self)
{
    UnkStruct_02264580 *p;
    unsigned int i;

    p = func_ov009_02264884(self);
    if (p != 0 && self->unk_284 != 0) {
        for (i = 0; i < func_ov009_02264394(p->unk_1C); i++) {
        }
        self->unk_284 = 0;
    }
}
