/* func_ov105_0229ef90 @ 0x0229ef90, 0x6c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int arg);
extern void func_020027f0(int arg);
extern void func_ov105_0229c320(void *p, int arg);
extern int func_ov105_0229c340(void *p, int arg);
extern void func_ov002_02208090(void *p, int arg);
extern void func_ov105_0229eefc(void *p);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

struct UnkStruct_0229ef90 {
    unsigned char pad_00[0x98];
    int unk_98;
};

void func_ov105_0229ef90(struct UnkStruct_0229ef90 *param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(6);
        func_ov105_0229c320(param, 2);
        if (func_ov105_0229c340(param, 0x100)) {
            func_ov002_02208090(param, 7);
            func_ov105_0229eefc(param);
        } else {
            func_ov105_0229c320(param, 1);
            func_ov002_022080a0(param, 5);
        }
    } else {
        func_ov002_02207e80(param, 6, 0, -16);
        param->unk_98 = func_ov002_02207f60(param);
    }
}
