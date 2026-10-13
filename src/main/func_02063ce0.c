/* func_02063ce0 @ 0x02063ce0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02063d04(unsigned char a, unsigned char b, unsigned char c);
extern void func_020e930c(int *ptr, int val);

typedef struct {
    int pad_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
} UnkStruct_02063ce0;

void func_02063ce0(UnkStruct_02063ce0 *param, unsigned char a, unsigned char b, unsigned char c)
{
    param->unk_08 = a;
    param->unk_09 = b;
    param->unk_0A = c;
    func_020e930c(&param->unk_04, func_02063d04(a, b, c));
}
