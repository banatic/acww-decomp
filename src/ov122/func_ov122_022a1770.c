/* func_ov122_022a1770 @ 0x022a1770, 0x98 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern const char data_ov122_022a2798[];
extern const char data_ov122_022a27b0[];
extern const char data_ov122_022a27c8[];

extern void func_02002d14(const void *a, int b, int c, int d, int e, int f);
extern void func_02002c6c(const void *a, int b, int c, int d, int e, int f);
extern void func_ov095_0229c000(void *a, const void *b);
extern void func_ov122_022a14c0(void *obj);
extern void func_ov095_0229bfd8(void *a, int b);
extern int func_02066648(int a);
extern void func_ov002_0220a448(int a, int b);
extern void func_0206e344(void *a, int b);
extern void func_ov122_022a15b8(void *obj, int a, int b);
extern void func_0206e2d0(void *a);

typedef struct {
    char pad_00[0xbc];
    int unk_BC;
    int unk_C0;
    char pad_C4[0x3ce8 - 0xc4];
} UnkStruct_022a1770;

typedef struct {
    char pad_00[0x3ce8];
    char field_at_3ce8;
} FarField;

void func_ov122_022a1770(UnkStruct_022a1770 *obj)
{
    int saved;

    saved = data_021fbe94;

    func_02002d14(data_ov122_022a2798, saved, 6, 1, 1, 9);
    func_ov095_0229c000(&obj->unk_C0, data_ov122_022a27b0);
    func_ov122_022a14c0(obj);
    func_ov095_0229bfd8(&obj->unk_C0, 6);
    func_02002c6c(data_ov122_022a27c8, saved, 6, 0x13d, 0x13d, 0x1e9);
    func_ov002_0220a448(func_02066648(obj->unk_BC), 4);
    func_0206e344((char *) obj + 0x3ce8, 3);
    func_ov122_022a15b8(obj, 1, 1);
    func_0206e2d0(&((FarField *) obj)->field_at_3ce8);
}
