/* func_020ab628 @ 0x020ab628, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x90];
} UnkStruct_020ab628;

extern void func_020ab778(UnkStruct_020ab628 *p, int a);
extern int func_020ab39c(int a);
extern void func_020ab774(UnkStruct_020ab628 *p, int a);
extern void func_020ab76c(UnkStruct_020ab628 *p, int a);
extern void func_020ab750(UnkStruct_020ab628 *p, int a);
extern void func_020ab758(UnkStruct_020ab628 *p, int a);

void func_020ab628(UnkStruct_020ab628 *base, int index, int arg3, int arg4, int arg5, int arg6, int arg7)
{
    UnkStruct_020ab628 *p;
    int tmp;

    p = &base[index];

    func_020ab778(p, arg3);
    tmp = func_020ab39c(arg4);
    func_020ab774(p, tmp);
    func_020ab76c(p, arg5);
    func_020ab750(p, arg7);
    if (arg6 != 0) {
        func_020ab758(p, arg6);
    }
}
