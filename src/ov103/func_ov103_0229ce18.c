/* func_ov103_0229ce18 @ 0x0229ce18, 0x6c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
} UnkStruct_0229ce18;

typedef struct {
    char pad_00[0x225c];
    UnkStruct_0229ce18 sub;
    char pad_2260[0x938];
    int unk_2B98;
    int unk_2B9C;
    char pad_2BA0[0x203];
    unsigned char byte_field;
} UnkStruct_0229ce18_2;

extern void func_ov002_02209d68(void *sub, int a, int b);
extern int func_ov103_0229ccb4(void *obj, int arg);
extern int func_ov103_0229cc80(void *obj, int arg);
extern void func_ov002_02209d38(void *sub, int a, int b, int c);
extern void func_ov002_02209d8c(void *sub);
extern void func_ov103_0229c964(void *obj);
extern void func_ov002_02208098(void *obj, int arg);

void func_ov103_0229ce18(void *obj, int arg1, int arg2)
{
    UnkStruct_0229ce18_2 *o = (UnkStruct_0229ce18_2 *) obj;

    o->byte_field = arg1;
    func_ov002_02209d68(&o->sub, o->unk_2B98, o->unk_2B9C);
    {
        int r7 = func_ov103_0229ccb4(obj, arg1);
        int r2 = func_ov103_0229cc80(obj, arg1);
        func_ov002_02209d38(&o->sub, r7, r2, arg2);
    }
    func_ov002_02209d8c(&o->sub);
    func_ov103_0229c964(obj);
    func_ov002_02208098(obj, 0x13);
}
