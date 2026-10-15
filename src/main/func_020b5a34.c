/* func_020b5a34 @ 0x020b5a34, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020dd828;
extern unsigned int data_021fbe94;
extern void func_0200471c(void);
extern unsigned int func_020e9948(unsigned int, unsigned int);

typedef struct {
    unsigned char pad_00[0x50];
    unsigned char unk_50;
    unsigned char pad_51[0xf];
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned int unk_68;
} UnkStruct_020b5a34;

int func_020b5a34(UnkStruct_020b5a34 *param)
{
    data_020dd828 = 3;
    func_0200471c();
    param->unk_50 = 0;
    param->unk_60 = data_021fbe94;
    param->unk_64 = func_020e9948(param->unk_60, 0x173fc);
    param->unk_68 = func_020e9948(param->unk_60, 0x173fc);
    return 1;
}
