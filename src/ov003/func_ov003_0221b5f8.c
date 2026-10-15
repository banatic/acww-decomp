/* func_ov003_0221b5f8 @ 0x0221b5f8, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5948(void *);
extern void *func_ov003_0221b75c(void *);
extern void *func_02032c50(void *);
extern void *func_02055764(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);
extern void func_ov003_0221b5a4(void *);
extern char data_ov003_022382ac;
extern char data_ov003_02238314;

struct UnkStruct_0221b5f8 {
    void *unk_00;
    char pad_04[0xEC - 4];
    void *unk_EC;
    char pad_F0[0x134 - 0xF0];
    char unk_134[4];
    char pad_138[0x1d0 - 0x138];
    char unk_1D0[4];
    char pad_1D4[0x274 - 0x1d4];
    char unk_274[4];
    char pad_278[0x2a4 - 0x278];
    char unk_2A4[4];
    char pad_2A8[0x328 - 0x2a8];
    char unk_328[4];
};

void *func_ov003_0221b5f8(void *arg)
{
    struct UnkStruct_0221b5f8 *obj = (struct UnkStruct_0221b5f8 *) arg;
    obj->unk_00 = &data_ov003_022382ac;
    obj->unk_EC = &data_ov003_02238314;
    func_020f5948(obj->unk_328);
    func_ov003_0221b75c(obj->unk_2A4);
    func_02032c50(obj->unk_274);
    func_02055764(obj->unk_1D0);
    func_02055764(obj->unk_134);
    func_02066994((void *) &obj->unk_EC);
    func_0203f080(obj);
    func_ov003_0221b5a4(obj);
    return obj;
}
