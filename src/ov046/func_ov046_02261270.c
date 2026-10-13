/* func_ov046_02261270 @ 0x02261270, 0x30 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1558(void);

typedef void (*Fn)(void *);

typedef struct {
    Fn *vtable;
    char pad_04[0xb0];
    int unk_B4;
    char pad_B8[0x0c];
    unsigned char unk_C4;
    unsigned char unk_C5;
} UnkStruct_02261270;

void func_ov046_02261270(UnkStruct_02261270 *self, int v)
{
    UnkStruct_02261270 *obj;

    obj->vtable[2](obj);
    obj = self;
    obj->unk_B4 = v;
    obj->unk_C4 = 0;
    obj->unk_C5 = 0x10 - func_020b1558();
}
