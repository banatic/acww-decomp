/* func_ov100_0229c4ec @ 0x0229c4ec, 0x3c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov100_0229c2a0(void *p, int n);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov100_0229c528(void *p, int n);
extern void func_0206fc4c(int n);
extern void func_0206fb14(void);

typedef struct {
    char pad_00[0x2928];
    unsigned char unk_2928;
} UnkStruct_0229c4ec;

void func_ov100_0229c4ec(UnkStruct_0229c4ec *p)
{
    func_ov100_0229c2a0(p, 8);
    RtcSendPxiCommand(0x28);
    p->unk_2928 = 5;
    func_ov002_02208098(p, 21);
    func_ov100_0229c528(p, 1);
    func_0206fc4c(0);
    func_0206fb14();
}
