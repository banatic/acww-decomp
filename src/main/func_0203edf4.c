/* func_0203edf4 @ 0x0203edf4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int arg);

typedef struct {
    char pad_00[0xe4];
    int unk_E4;
} UnkStruct_0203edf4;

void func_0203edf4(UnkStruct_0203edf4 *obj, int arg)
{
    obj->unk_E4 = FX_MulFunc(arg);
}
