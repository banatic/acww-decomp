/* func_ov112_022a1520 @ 0x022a1520, 0x80 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a1520 {
    char pad_00[0xA4];
    int unk_A4;
    int unk_A8;
};

extern int func_ov112_0229fe70(void *, int);
extern int func_ov112_0229efbc(void *);
extern void func_ov112_0229fe50(void *, int);
extern void func_ov112_0229f058(void *);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f60(void *);

void func_ov112_022a1520(struct UnkStruct_022a1520 *obj)
{
    if (func_ov112_0229fe70(obj, 0x2000) != 0 || func_ov112_0229efbc(obj) != 0) {
        func_ov112_0229fe50(obj, 0x40);
        func_ov112_0229f058(obj);
        func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
        func_ov002_02207f04(obj, 2, 0, 0, 0x30);
        func_ov002_02207e80(obj, 4, 0, -8);
        func_ov002_02208090(obj, 0xb);
        obj->unk_A4 = func_ov002_02207f60(obj);
        obj->unk_A8 = obj->unk_A4;
    }
}
