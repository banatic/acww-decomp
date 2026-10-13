/* func_ov003_02223208 @ 0x02223208, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203f8d0(void *, void *);
extern void func_020e96c8(void *, int, int, int);
extern void func_020e9774(void *, int);
extern void func_0205510c(void *, int);
extern int func_02065604(void);
extern void NNS_G3dMdlSetMdlEmi(void *, int, unsigned short);

typedef struct {
    unsigned int data[12];
} Global48;

extern Global48 data_021fbe48;

typedef struct {
    int unk_00;
    int pad_04;
    void *unk_08;
    char pad_0C[0x58];
    void *unk_64;
    char pad_68[4];
    Global48 unk_6C;
    char pad_9C[0x24];
    void *unk_C0;
} UnkStruct_02223208;

void func_ov003_02223208(UnkStruct_02223208 *p)
{
    volatile unsigned short pair[2];
    struct {
        int a;
        int b;
        int c;
    } local;
    int ret1;

    if (p->unk_00 != 1) {
        return;
    }

    ret1 = func_0203f8d0(&local, &p->unk_C0);
    func_020e96c8(&data_021fbe48, local.a, local.b, local.c);
    func_020e9774(&data_021fbe48, ret1);
    p->unk_6C = data_021fbe48;
    func_0205510c(&p->unk_08, 0);
    pair[0] = (unsigned short) func_02065604();
    pair[1] = pair[0];
    NNS_G3dMdlSetMdlEmi(p->unk_64, 0, pair[1]);
}
