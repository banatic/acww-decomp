/* func_ov099_0229d168 @ 0x0229d168, 0x38 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d168 {
    char pad_00[0x2274];
    char unk_2274[1];
    char pad_2275[0x457];
    char unk_26CC[1];
    char pad_26CD[0x23d];
    unsigned char unk_290A;
};

extern int func_ov002_0220b8ac(void *ptr, int arg);
extern void func_ov002_02208098(void *self, unsigned char val);
extern void func_0208e5cc(void *ptr);

void func_ov099_0229d168(struct UnkStruct_0229d168 *self)
{
    if (func_ov002_0220b8ac(self->unk_26CC, 0)) {
        func_ov002_02208098(self, self->unk_290A);
        func_0208e5cc(self->unk_2274);
    }
}
