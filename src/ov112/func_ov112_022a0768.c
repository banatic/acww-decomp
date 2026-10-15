/* func_ov112_022a0768 @ 0x022a0768, 0x30 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bf48(void *ptr);
extern int func_ov002_0220b8ac(void *ptr, int flag);
extern int func_ov112_0229fefc(void *ptr);

typedef struct {
    char pad_00[0x244];
    int unk_244;
    char pad_248[0x13c];
    int unk_384;
} UnkStruct_022a0768;

void func_ov112_022a0768(UnkStruct_022a0768 *a)
{
    func_ov095_0229bf48(&a->unk_384);
    if (func_ov002_0220b8ac(&a->unk_244, 1) != 0) {
        func_ov112_0229fefc(a);
    }
}
