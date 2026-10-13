/* func_ov121_0229b6f0 @ 0x0229b6f0, 0x74 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov002_02208098(void *s, int a);
extern void func_ov002_02207ce4(void *p, int a);
extern int func_ov121_0229ad68(void *s);
extern void func_ov121_02299a4c(void *s, int a);
extern void func_ov002_02207d24(void *p, int a);
extern void RtcSendPxiCommand(int a);
extern void func_ov002_02207d00(void *p);

typedef struct {
    char pad_00[0xad];
    unsigned char unk_AD;
    unsigned char unk_AE;
    unsigned char unk_AF;
} UnkStruct_0229b6f0;

void func_ov121_0229b6f0(UnkStruct_0229b6f0 *s)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(s, 0);
        func_ov002_02207ce4((char *) s + 0x2d8, 0x3c);
    } else {
        if (func_ov121_0229ad68(s)) {
            s->unk_AE = s->unk_AD;
            func_ov121_02299a4c(s, 4);
            s->unk_AF = 0x18;
            func_ov002_02208098(s, 2);
            func_ov002_02207d24((char *) s + 0x2d8, 1);
            RtcSendPxiCommand(0xd);
        } else {
            func_ov002_02207d00((char *) s + 0x2d8);
        }
    }
}
