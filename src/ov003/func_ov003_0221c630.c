/* func_ov003_0221c630 @ 0x0221c630, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_02238934;
extern char data_ov003_022389f8;

extern void *func_ov003_0221c490(void *sub);
extern void *func_ov009_0226539c(void *obj);
extern void func_020edf54(void *obj);

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xe8];
    void *unk_EC;
    unsigned char pad_F0[0x1c4];
    unsigned char unk_2B4;
} UnkStruct_0221c630;

void *func_ov003_0221c630(UnkStruct_0221c630 *obj)
{
    obj->unk_00 = &data_ov003_02238934;
    obj->unk_EC = &data_ov003_022389f8;
    func_ov003_0221c490(&obj->unk_2B4);
    func_ov009_0226539c(obj);
    func_020edf54(obj);
    return obj;
}
