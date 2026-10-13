/* func_ov105_0229d230 @ 0x0229d230, 0x64 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d76c(void *arg, unsigned char byte);
extern int func_ov105_0229d75c(void *arg, unsigned char byte);
extern int func_ov105_0229d428(void *arg, unsigned char byte);
extern void func_ov002_02207cf0(void *ptr);
extern void func_ov002_02207cf8(void *ptr);

struct UnkStruct_0229d230 {
    char pad_00[0x2b6];
    unsigned char unk_2B6;
    char pad_2B7[3];
    unsigned char unk_2BA;
    char pad_2BB[0x23bc - 0x2bb];
    char sub;
};

void func_ov105_0229d230(struct UnkStruct_0229d230 *arg)
{
    if (func_ov105_0229d76c(arg, arg->unk_2BA) || func_ov105_0229d75c(arg, arg->unk_2BA)) {
        if (func_ov105_0229d428(arg, arg->unk_2BA) != 0) {
            func_ov002_02207cf0(&arg->sub);
        } else {
            arg->unk_2B6 = arg->unk_2BA;
            func_ov002_02207cf8(&arg->sub);
        }
    } else {
        func_ov002_02207cf0(&arg->sub);
    }
}
