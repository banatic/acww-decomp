/* func_0208ed60 @ 0x0208ed60, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208ecd0(void *p);
extern void func_0208a1f0(void *dest, void *src);
extern void func_0208a1ec(void *dest, int value);
extern void func_0208a144(void *p);
extern int data_020d5b54;

typedef struct UnkStruct_0208ed60 {
    char pad_00[0xc];
    char unk_0C[0x14];
    int unk_20;
} UnkStruct_0208ed60;

void func_0208ed60(UnkStruct_0208ed60 *arg)
{
    if (func_0208ecd0(arg)) {
        return;
    }
    arg->unk_20 = 3;
    func_0208a1f0(arg->unk_0C, &data_020d5b54);
    func_0208a1ec(arg->unk_0C, 1);
    arg = (UnkStruct_0208ed60 *) &arg->unk_0C;
    func_0208a144(arg);
}
