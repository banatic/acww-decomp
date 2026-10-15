/* func_020aa09c @ 0x020aa09c, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020aa09c {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char sub[0x148];
    unsigned char sub2[0x38];
    int unk_18C;
    int unk_190;
    int unk_194;
} UnkStruct_020aa09c;

extern int func_020ac8c8(unsigned char *s);
extern void func_020aae40(unsigned char *s);
extern void func_020a9ddc(UnkStruct_020aa09c *p);
extern void func_020ac444(unsigned char *s);
extern void func_020ac424(unsigned char *s);
extern void func_020ac3ec(unsigned char *s);
extern void func_020ac8a8(unsigned char *s);
extern int func_0209d368(int a, int b);
extern void func_020ac39c(unsigned char *s, int a, int b);
extern void func_020ac384(unsigned char *s);
extern void RtcSendPxiCommand(int cmd);

void func_020aa09c(UnkStruct_020aa09c *p)
{
    p->unk_08 = 1;
    func_020ac8c8(p->sub);
    func_020aae40(p->sub2);
    func_020a9ddc(p);
    func_020ac444(p->sub);
    func_020ac424(p->sub);
    func_020ac3ec(p->sub);
    func_020ac8a8(p->sub);
    p->unk_194 = func_0209d368(100, 2) + 3;
    p->unk_18C = func_0209d368(100, 4) + 5;
    p->unk_190 = func_0209d368(100, 5) - 5;
    func_020ac39c(p->sub, p->unk_18C, p->unk_190 + 4);
    func_020ac384(p->sub);
    RtcSendPxiCommand(0x13);
}
