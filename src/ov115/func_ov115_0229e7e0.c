/* func_ov115_0229e7e0 @ 0x0229e7e0, 0x58 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void *obj);
extern void func_ov002_02209ccc(void *obj);
extern void func_ov114_0229da18(void *obj);
extern void func_02138d6c(void *ptr, int a, int b, void (*cb)(void), void (*arg)(void));
extern void func_02070be8(void);
extern void func_02070c08(void);
extern char data_ov115_0229e8b8;

typedef struct {
    void *vtable;
    char pad_04[0x90];
    char unk_94;
    char pad_95[0x63];
    char unk_F8;
    char pad_F9[0x12bf];
    char unk_13B8;
} UnkStruct_0229e7e0;

void *func_ov115_0229e7e0(void)
{
    UnkStruct_0229e7e0 *obj = func_ov002_02207f80(0x1430);
    if (obj) {
        func_ov002_0220830c(obj);
        obj->vtable = &data_ov115_0229e8b8;
        func_ov002_02209ccc(&obj->unk_94);
        func_ov114_0229da18(&obj->unk_F8);
        func_02138d6c(&obj->unk_13B8, 1, 0x6c, func_02070c08, func_02070be8);
    }
    return obj;
}
