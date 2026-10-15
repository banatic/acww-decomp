/* func_020204f4 @ 0x020204f4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int arg);
extern int func_020036e8(int arg);
extern int func_0202da38(void *p0, void *p1, void *p2, int p3, int p4, int p5, int p6, int p7, int p8);
extern int data_020c8ab0;

typedef struct UnkStruct_020204f4 {
    unsigned char pad_00[0x830];
    int something;
} UnkStruct_020204f4;

typedef struct {
    unsigned char pad_00[0x100];
    struct UnkStruct_020204f4 *inner;
    unsigned char unk_104[30];
    unsigned char byte;
} UnkStruct_020204f4_2;

typedef struct {
    void *ptr;
    unsigned char ch;
} Result;

void func_020204f4(UnkStruct_020204f4_2 *obj, Result *res)
{
    int arg5;
    int arg6;
    arg5 = func_020036e8(func_0208150c(obj->inner->something));
    arg6 = data_020c8ab0;
    func_0202da38(obj, obj->unk_104, (char *) obj + 0x122, 30, arg5, arg6, 1, 10, 2);
    res->ptr = obj->unk_104;
    res->ch = obj->byte;
}
