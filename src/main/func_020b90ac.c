/* func_020b90ac @ 0x020b90ac, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xE6];
    unsigned char unk_E6;
    unsigned char unk_E7;
} UnkStruct_020b90ac;

extern void func_0208aaa0(UnkStruct_020b90ac *param);
extern void func_020b8f20(UnkStruct_020b90ac *param);

void func_020b90ac(UnkStruct_020b90ac *param)
{
    param->unk_E7 = param->unk_E6;
    func_0208aaa0(param);
    func_020b8f20(param);
}
