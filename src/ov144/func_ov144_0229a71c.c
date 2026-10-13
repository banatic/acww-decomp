/* func_ov144_0229a71c @ 0x0229a71c, 0x7c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a71c {
    unsigned char pad_00[0xba];      // 0x00
    short unk_BA;                    // 0xba
    short unk_BC;                    // 0xbc
    unsigned char pad_BE[2];         // 0xbe
    unsigned char unk_C0;            // 0xc0
    unsigned char pad_C1[0x7ab];     // 0xc1
    unsigned short array_86c[0x400]; // 0x86c
};

extern void func_ov144_0229a6c8(struct UnkStruct_0229a71c *p);
extern void func_ov144_02299660(struct UnkStruct_0229a71c *p, int a);
extern void func_ov144_02299c5c(struct UnkStruct_0229a71c *p, int a);
extern void func_ov002_02208098(struct UnkStruct_0229a71c *p, int a);
extern void func_ov144_02299694(struct UnkStruct_0229a71c *p, int a);
extern void func_0206fc4c(int a);
extern void func_0206f674(int a);
extern void func_ov002_02208090(struct UnkStruct_0229a71c *p, int a);
extern void RtcSendPxiCommand(int cmd);

int func_ov144_0229a71c(struct UnkStruct_0229a71c *p)
{
    if (p->unk_BA == -1) {
        return 0;
    }

    if (p->unk_BC != -1) {
        func_ov144_0229a6c8(p);
        return 0;
    }

    func_ov144_02299660(p, 0x20);
    p->unk_C0 = 5;
    func_ov144_02299c5c(p, 8);
    func_ov002_02208098(p, 0xb);
    func_ov144_02299694(p, p->unk_BA);
    func_0206fc4c(1);
    func_0206f674(p->array_86c[p->unk_BA]);
    func_ov002_02208090(p, 2);
    RtcSendPxiCommand(0x55);
    return 1;
}
