/* func_ov111_022a027c @ 0x022a027c, 0x7c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

struct SubType {
    int pad_00;
};

struct Param {
    unsigned char pad_00[0x9e];
    unsigned char unk_9E;
    unsigned char unk_9F;
    unsigned char unk_A0;
    unsigned char pad_A1[0x0b];
    struct SubType unk_AC;
};

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(struct Param *p, int x);
extern int func_ov002_02208008(struct Param *p);
extern int func_ov111_0229f430(struct Param *p, int x);
extern void func_ov095_0229b3ec(struct SubType *p);
extern void func_ov111_0229f524(struct Param *p);
extern void func_ov111_0229f10c(struct Param *p);
extern void func_ov111_0229fd08(struct Param *p);
extern void func_ov111_0229efec(struct Param *p);
extern void func_ov111_0229efb8(struct Param *p, int x);
extern void RtcSendPxiCommand(int cmd);

void func_ov111_022a027c(struct Param *p)
{
    if (!(data_021fbe40 & 1)) {
        func_ov002_02208098(p, 9);
        if (p->unk_9F == p->unk_A0) {
            func_ov111_0229efb8(p, 1);
        }
    } else {
        if (func_ov111_0229f430(p, func_ov002_02208008(p)) == 1) {
            func_ov095_0229b3ec(&p->unk_AC);
            func_ov111_0229f524(p);
            p->unk_A0 = p->unk_9E;
            func_ov111_0229f10c(p);
            RtcSendPxiCommand(21);
        }
    }
    func_ov111_0229fd08(p);
    func_ov111_0229efec(p);
}
