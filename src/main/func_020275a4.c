/* func_020275a4 @ 0x020275a4, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209b4d4(int);
extern void func_0209bb90(int, int);
extern int func_0209b4cc(int, int);
extern int func_0208150c(int);
extern void func_0207bae8(int *, int, int, int);
extern void func_02015094(void *);

typedef struct {
    int lo;
    int hi;
} DoubleWord;

extern int data_021e5a2c;
extern DoubleWord data_020d94a8;
extern void func_0202dbf0(void *, DoubleWord);

typedef struct UnkStruct_020275a4 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_020275a4;

typedef struct Param {
    char pad_00[0x100];
    UnkStruct_020275a4 *sub;
    char pad_104[0x5c];
    int unk_160;
} Param;

void func_020275a4(Param *param)
{
    int r4;
    int r2;

    func_0209bb90(func_0209b4d4(param->unk_160), 1);
    r4 = func_0209b4cc(param->unk_160, 0);
    r2 = func_0208150c(param->sub->unk_830);
    func_0207bae8(&data_021e5a2c, r4, r2, -20);
    func_02015094(param);
    func_0202dbf0(param, data_020d94a8);
}
