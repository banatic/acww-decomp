/* func_ov103_0229db7c @ 0x0229db7c, 0x70 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2b8c];
    int unk_2B8C;
} UnkStruct_0229db7c;

extern int func_ov002_02207f3c(UnkStruct_0229db7c *, int);
extern void func_020027f0(int);
extern void func_ov103_0229c2d4(UnkStruct_0229db7c *, int);
extern int func_ov103_0229c2f4(UnkStruct_0229db7c *, int);
extern void func_ov002_02208090(UnkStruct_0229db7c *, int);
extern void func_ov103_0229daf4(UnkStruct_0229db7c *);
extern void func_ov002_022080a0(UnkStruct_0229db7c *, int);
extern void func_ov002_02207e80(UnkStruct_0229db7c *, int, int, int);
extern int func_ov002_02207f60(UnkStruct_0229db7c *);

void func_ov103_0229db7c(UnkStruct_0229db7c *obj)
{
    if (func_ov002_02207f3c(obj, 0) != 0) {
        func_020027f0(6);
        func_ov103_0229c2d4(obj, 2);
        if (func_ov103_0229c2f4(obj, 0x100) != 0) {
            func_ov002_02208090(obj, 5);
            func_ov103_0229daf4(obj);
        } else {
            func_ov103_0229c2d4(obj, 1);
            func_ov002_022080a0(obj, 5);
        }
    } else {
        func_ov002_02207e80(obj, 6, 0, 0);
    }
    obj->unk_2B8C = func_ov002_02207f60(obj);
}
