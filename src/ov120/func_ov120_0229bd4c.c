/* func_ov120_0229bd4c @ 0x0229bd4c, 0x60 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x94];
    int unk_94;
    unsigned short unk_98;
} UnkStruct_0229bd4c;

extern int func_ov002_02207f3c(UnkStruct_0229bd4c *, int);
extern void func_020027f0(int);
extern void func_ov120_0229a428(UnkStruct_0229bd4c *, int);
extern void func_ov002_022080a0(UnkStruct_0229bd4c *, int);
extern void func_ov002_02207e80(UnkStruct_0229bd4c *, int, int, int);
extern int func_ov002_02207f60(UnkStruct_0229bd4c *);

void func_ov120_0229bd4c(UnkStruct_0229bd4c *arg0)
{
    if (func_ov002_02207f3c(arg0, 0)) {
        func_020027f0(4);
        func_020027f0(6);
        func_ov120_0229a428(arg0, 4);
        func_ov002_022080a0(arg0, 5);
    } else {
        func_ov002_02207e80(arg0, 4, 0, 0);
        func_ov002_02207e80(arg0, 6, 0, 0x50 - arg0->unk_98);
        arg0->unk_94 = func_ov002_02207f60(arg0);
    }
}
