/* func_02027f28 @ 0x02027f28, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_0209b4cc(int, int);
extern void func_0207bae8(int, int, int, int);
extern void func_0209b56c(int);

typedef struct {
    char pad_00[0x830];
    int value;
} UnkStruct_02027f28;

typedef struct {
    char pad_00[0x100];
    UnkStruct_02027f28 *ptr;
    char pad_104[0x5C];
    int unk_160;
} UnkStruct_02027f28_2;

extern unsigned char data_021e5a2c[];

void func_02027f28(UnkStruct_02027f28_2 *p)
{
    int a = func_0208150c(p->ptr->value);
    int b = func_0209b4cc(p->unk_160, 1);
    func_0207bae8((unsigned int) data_021e5a2c, a, b, -20);
    func_0209b56c(p->unk_160);
}
