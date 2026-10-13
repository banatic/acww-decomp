/* func_0209af44 @ 0x0209af44, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003780(void *);
extern void func_0209bd80(void *);
extern void func_02003738(void *);
extern void func_0209bd5c(void *);
extern void MI_CpuFill8(void *, int, int);

typedef struct {
    char unk_00[0x10];
    char sub1[0x0c];
    int unk_1C;
    int unk_20;
    char sub2;
} UnkStruct_0209af44;

void *func_0209af44(UnkStruct_0209af44 *arg)
{
    func_02003780(arg);
    func_0209bd80(arg->sub1);
    arg->unk_1C = 0;
    arg->unk_20 = 0;
    func_02003738(arg);
    func_0209bd5c(arg->sub1);
    arg->unk_1C = 0;
    arg->unk_20 = 0;
    MI_CpuFill8(&arg->sub2, 0, 1);
    return arg;
}
