/* func_020f50e4 @ 0x020f50e4, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f50e4 {
    unsigned int a;
    unsigned int b;
    unsigned int unk_08;
    unsigned int unk_0C;
};

extern int func_020f5e50(unsigned int *ptr, int n);
extern int func_020f5e24(int val);
extern int func_020f5c64(unsigned int *ptr, int n);
extern void NNS_SndPlayerSetVolume(unsigned int *ptr, int n);
extern void func_0210b634(unsigned int *ptr, int n1, int n2);

void func_020f50e4(struct UnkStruct_020f50e4 *p)
{
    int r5, r4;
    r5 = func_020f5e24(func_020f5e50(&p->unk_0C, 0));
    r4 = func_020f5c64(&p->unk_0C, 0);
    NNS_SndPlayerSetVolume(&p->unk_08, r5);
    func_0210b634(&p->unk_08, 0xff, r4);
}
