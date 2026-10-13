/* func_ov141_0229a4ac @ 0x0229a4ac, 0x3c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a4ac {
    char pad_00[0xa38];
    int unk_A38;
} UnkStruct_0229a4ac;

extern int func_ov141_0229a490(UnkStruct_0229a4ac *obj);
extern int func_ov141_0229a470(UnkStruct_0229a4ac *obj);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int a);
extern void func_ov141_0229a3a4(UnkStruct_0229a4ac *obj);

void func_ov141_0229a4ac(UnkStruct_0229a4ac *obj)
{
    int r4, r2;
    r4 = func_ov141_0229a490(obj);
    r2 = func_ov141_0229a470(obj);
    func_ov002_0220a0b4(&obj->unk_A38, r4, r2);
    func_ov002_0220a374(&obj->unk_A38, 7);
    func_ov141_0229a3a4(obj);
}
