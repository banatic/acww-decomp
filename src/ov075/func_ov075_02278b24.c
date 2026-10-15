/* func_ov075_02278b24 @ 0x02278b24, 0x40 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_020644cc(int);
extern char data_ov075_02279aa8[];

typedef struct {
    char pad_00[0xb8];
    void *ptr;
} UnkStruct_02278b24;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_02278b24_2;

void func_ov075_02278b24(UnkStruct_02278b24 *self, UnkStruct_02278b24_2 *obj)
{
    unsigned char flag;

    obj->unk_04 = 0x1a;
    flag = ((unsigned char *) self->ptr)[0x718];
    if (flag != 0) {
        if (func_02099020(func_020984e8(), 6)) {
            obj->unk_04 = func_020644cc(4) + 0xc;
        }
    }
    obj->unk_00 = data_ov075_02279aa8;
}
