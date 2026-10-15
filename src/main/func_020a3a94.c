/* func_020a3a94 @ 0x020a3a94, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a0284(int, int);
extern int func_020984e8(void);
extern void func_02098ff8(int, int);
extern void func_020a6ec0(void *);

typedef struct {
    char pad_00[0x64];
    void *unk_64;
} UnkStruct_020a3a94;

extern UnkStruct_020a3a94 *data_020ccf94;

void func_020a3a94(int arg0)
{
    int a;
    int b;
    a = ((int) (func_020a0284(arg0, 0), arg0));
    b = func_020984e8();
    func_02098ff8(b, 2);
    func_020a6ec0(data_020ccf94->unk_64);
}
