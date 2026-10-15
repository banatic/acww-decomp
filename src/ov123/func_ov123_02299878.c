/* func_ov123_02299878 @ 0x02299878, 0x48 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299878 {
    char pad_00[0xB1];
    unsigned char b1;
    unsigned char b2;
    char pad_B3;
    unsigned char b4;
    unsigned char b5;
} UnkStruct_02299878;

extern unsigned char *func_ov002_02208098(UnkStruct_02299878 *p, unsigned char value);
extern void func_ov123_02299630(UnkStruct_02299878 *p, int a);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov123_02299878(UnkStruct_02299878 *p)
{
    p->b1 = 0;
    p->b2 = 0x22;
    func_ov002_02208098(p, 2);
    func_ov123_02299630(p, 0x2000);
    p->b4 = data_021f6c58;
    p->b5 = data_021f6c54;
}
