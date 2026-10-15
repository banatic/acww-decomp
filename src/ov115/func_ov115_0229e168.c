/* func_ov115_0229e168 @ 0x0229e168, 0x88 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void);
extern int func_ov002_02208008(void *);
extern int func_ov114_0229c410(void *, int);
extern int func_ov090_02299078(int);
extern int func_ov090_02299098(int);
extern void func_ov115_0229dfa8(void *);
extern void func_ov115_0229de60(void *);
extern void func_ov115_0229ddf8(void *);
extern int func_ov115_0229e4cc(void *, int);

typedef struct {
    char pad_00[2];
    unsigned short flags;
} UnkStruct_0229e168;
extern UnkStruct_0229e168 data_021fbe40;

typedef struct {
    char pad_00[0xf8];
    char unk_F8;
} UnkStruct_0229e168_2;

void func_ov115_0229e168(UnkStruct_0229e168_2 *param)
{
    unsigned short flags;

    if (func_ov002_02208014() != 0) {
        func_ov115_0229dfa8(param);
        return;
    }
    if (func_ov114_0229c410(&param->unk_F8, func_ov002_02208008(param)) != 0) {
        func_ov115_0229de60(param);
        return;
    }
    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov115_0229ddf8(param);
        return;
    }
    if (flags & 0x100) {
        func_ov115_0229e4cc(param, func_ov090_02299078(2));
        return;
    }
    if (flags & 0x200) {
        func_ov115_0229e4cc(param, func_ov090_02299098(2));
    }
}
