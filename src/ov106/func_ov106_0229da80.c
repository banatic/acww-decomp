/* func_ov106_0229da80 @ 0x0229da80, 0x54 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229da80 {
    unsigned char flag;
};

struct Big {
    char pad_00[0xbe];
    struct UnkStruct_0229da80 sub;
    char pad_BF[0x22a0 - (0xbe + 1)];
    char unk_22A0;
    char pad_22A1[0x3fb4 - (0x22a0 + 1)];
    char unk_3FB4;
};

extern int func_0208e484(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void *func_ov002_0220a720(void *, int);
extern void RtcSendPxiCommand(int);

void func_ov106_0229da80(struct Big *p)
{
    struct UnkStruct_0229da80 *s;
    if (func_0208e484(&p->unk_22A0) == 0) {
        return;
    }
    func_ov002_02208098((void *) (p), 0x1f);
    s = &p->sub;
    if (s->flag != 0) {
        func_ov002_0220a720(&p->unk_3FB4, 4);
        RtcSendPxiCommand(0x28);
    } else {
        func_ov002_0220a720(&p->unk_3FB4, 3);
        RtcSendPxiCommand(0x27);
    }
}
