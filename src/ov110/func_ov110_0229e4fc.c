/* func_ov110_0229e4fc @ 0x0229e4fc, 0x68 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229e4fc {
    char pad_00[0x9c];
    int unk_9C;
} UnkStruct_0229e4fc;

extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern void func_ov110_0229c2a8(void *, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov110_0229e4b0(void *);
extern int func_ov002_02207f60(void *);

void func_ov110_0229e4fc(UnkStruct_0229e4fc *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(4);
        func_ov110_0229c2a8(param, 0x80);
        func_ov002_02207f04(param, 8, 0, 0, 0x30);
        func_ov002_02207e80(param, 6, 0, 0);
        func_ov002_02208090(param, 6);
        func_ov110_0229e4b0(param);
    } else {
        func_ov002_02207e80(param, 4, 0, 0);
        param->unk_9C = func_ov002_02207f60(param);
    }
}
