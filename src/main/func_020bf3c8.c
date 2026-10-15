/* func_020bf3c8 @ 0x020bf3c8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Param0Struct {
    char pad_00[0x28];
    int unk_28;
};

struct UnkStruct_020bf3c8 {
    int a;
    int b;
    int c;
};

extern int data_020ca0e8;
extern void func_020bf3ec(struct Param0Struct *p0, struct UnkStruct_020bf3c8 *p1, int p2);

void func_020bf3c8(struct Param0Struct *param0, int param1)
{
    struct UnkStruct_020bf3c8 local;
    local.a = param0->unk_28;
    local.b = 0;
    local.c = data_020ca0e8;
    func_020bf3ec(param0, &local, param1);
}
