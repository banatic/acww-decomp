/* func_ov100_0229d71c @ 0x0229d71c, 0x6c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
} UnkStruct_0229d71c;

typedef struct {
    char pad_00[0x225c];
    UnkStruct_0229d71c sub;
    char pad1[0x28d4 - 0x225c - sizeof(UnkStruct_0229d71c)];
    int unk_28D4;
    int unk_28D8;
    char pad_28DC[0x2920 - 0x28d8 - 4];
    unsigned char byte_field;
} UnkStruct_0229d71c_2;

extern void func_ov002_02209d68(void *sub, int a, int b);
extern int func_ov100_0229d42c(void *obj, int arg);
extern int func_ov100_0229d3d8(void *obj, int arg);
extern int func_ov002_02209d38(void *sub, int a, int b, int c);
extern int func_ov002_02209d8c(void *sub);
extern void func_ov100_0229cdf4(void *obj);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov100_0229d71c(void *obj, int arg1, int arg2)
{
    UnkStruct_0229d71c_2 *o = (UnkStruct_0229d71c_2 *) obj;

    o->byte_field = arg1;
    func_ov002_02209d68(&o->sub, o->unk_28D4, o->unk_28D8);
    {
        int r7 = func_ov100_0229d42c(obj, arg1);
        int r2 = func_ov100_0229d3d8(obj, arg1);
        func_ov002_02209d38(&o->sub, r7, r2, arg2);
    }
    func_ov002_02209d8c(&o->sub);
    func_ov100_0229cdf4(obj);
    func_ov002_02208098((void *) (obj), 0x10);
}
