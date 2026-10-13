/* func_ov101_0229cb60 @ 0x0229cb60, 0x40 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void *s, int arg1);
extern char *func_ov101_0229ce1c(void *s, int arg1);
extern void func_ov094_0229ab1c(void *a, void *b);
extern void func_ov094_0229b98c(void *a);
extern void func_ov101_0229cba0(void *s);

struct UnkStruct_0229cb60 {
    char pad_00[0xf4];
    char unk_F4;
    char pad_F5[0xb54 - 0xf4 - 1];
    char unk_B54;
};

void func_ov101_0229cb60(struct UnkStruct_0229cb60 *s, int arg1)
{
    char *tmp;

    if (func_ov101_0229ce38(s, arg1)) {
        tmp = func_ov101_0229ce1c(s, arg1);
        func_ov094_0229ab1c(&s->unk_F4, tmp);
        func_ov094_0229b98c(&s->unk_B54);
    } else {
        func_ov101_0229cba0(s);
    }
}
