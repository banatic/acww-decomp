/* func_ov138_0229cad4 @ 0x0229cad4, 0x24 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cad4 {
    unsigned char pad_00[0x94];
    unsigned char unk_94;
    unsigned char pad_95[3];
    void *unk_98;
};

extern int func_0208e484(void *);
extern void func_ov138_0229c66c(struct UnkStruct_0229cad4 *);
extern void func_ov002_02208098(struct UnkStruct_0229cad4 *, unsigned char);

void func_ov138_0229cad4(struct UnkStruct_0229cad4 *arg)
{
    if (func_0208e484(&arg->unk_98) != 0) {
        func_ov138_0229c66c(arg);
        func_ov002_02208098(arg, arg->unk_94);
    }
}
