/* func_020265fc @ 0x020265fc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202cbdc(unsigned short *p, int a, int b, unsigned char c, unsigned char d);

typedef struct {
    char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
} UnkStruct_020265fc;

void func_020265fc(unsigned short *param0, UnkStruct_020265fc *param1)
{
    int result;
    *param0 = 0xfff1;
    result = func_0202cbdc(param0, 2, 3, param1->unk_04, param1->unk_03);
    if (result != 0) {
        return;
    }
    result = func_0202cbdc(param0, 0, 1, param1->unk_04, param1->unk_03);
    if (result != 0) {
        return;
    }
    func_0202cbdc(param0, 4, 4, param1->unk_04, param1->unk_03);
}
