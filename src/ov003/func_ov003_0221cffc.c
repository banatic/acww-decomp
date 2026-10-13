/* func_ov003_0221cffc @ 0x0221cffc, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d4];
    signed char flag;
    unsigned char value;
} UnkStruct_0221cffc;

typedef struct {
    unsigned int pad_00[3];
    unsigned int unk_0C;
} UnkStruct_0221cffc_2;

typedef struct {
    char pad_00[0xb0];
    UnkStruct_0221cffc_2 *ptr;
} UnkStruct_0221cffc_3;

void func_ov003_0221cffc(UnkStruct_0221cffc *s, int comp, UnkStruct_0221cffc_3 *t)
{
    if (comp == s->flag) {
        t->ptr->unk_0C &= 0xffe0ffff;
        t->ptr->unk_0C |= ((unsigned int) s->value << 16);
    }
}
