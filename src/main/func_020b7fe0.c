/* func_020b7fe0 @ 0x020b7fe0, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203f844(void *dst, int src);
extern void func_020b7fa0(void *dst, void *a, void *b, void *c, int e, unsigned char f);

typedef struct {
    int data[3];
} UnkStruct_020b7fe0;

void func_020b7fe0(void *param0, int param1, int param2, int param3, int arg4, unsigned char arg5)
{
    UnkStruct_020b7fe0 local0;
    UnkStruct_020b7fe0 local1;
    UnkStruct_020b7fe0 local2;

    func_0203f844(&local0, param1);
    func_0203f844(&local1, param2);
    func_0203f844(&local2, param3);
    func_020b7fa0(param0, &local0, &local1, &local2, arg4, arg5);
}
