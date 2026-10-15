/* func_0208fb54 @ 0x0208fb54, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020d0bac[];
extern void func_02004658(int value);

typedef struct {
    unsigned char pad_00[0x1c];
    int unk_1C;
    unsigned char unk_20;
} UnkStruct_0208fb54;

void func_0208fb54(UnkStruct_0208fb54 *param)
{
    int index = param->unk_1C;
    unsigned short value = data_020d0bac[index];
    param->unk_20 = 1;
    func_02004658(value);
}
