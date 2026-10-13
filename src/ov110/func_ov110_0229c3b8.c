/* func_ov110_0229c3b8 @ 0x0229c3b8, 0x140 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb0];
    unsigned short a[15];
    unsigned short b[15];
    char pad_EC[0xfc - 0xec];
    unsigned char st;
} UnkStruct_0229c3b8;

extern void func_ov110_0229c2a8(UnkStruct_0229c3b8 *, int);
extern int func_0206fca4(void);
extern void RtcSendPxiCommand(int);
extern void func_ov002_02208098(UnkStruct_0229c3b8 *, int);
extern void func_ov110_0229c4f8(UnkStruct_0229c3b8 *, int);
extern int func_ov110_0229c388(UnkStruct_0229c3b8 *, unsigned short *);
extern void func_0206fc4c(int);
extern void func_0206faf8(unsigned short *);
extern void func_0206fc80(int);
extern void func_ov110_0229c324(UnkStruct_0229c3b8 *, int);
extern void MI_CpuCopy8(void *, const void *, int);
extern const unsigned short data_021f3a68[];
extern const unsigned short data_021f3a86[];

void func_ov110_0229c3b8(UnkStruct_0229c3b8 *s, int flag)
{
    int m;
    int r;
    int i, j;

    func_ov110_0229c2a8(s, 8);
    m = func_0206fca4();
    if (m == 0x20) {
        RtcSendPxiCommand(0x28);
    } else {
        RtcSendPxiCommand(0x27);
    }
    if (flag != 0) {
        s->st = 5;
    } else {
        s->st = 0;
    }
    func_ov002_02208098(s, 0x15);
    func_ov110_0229c4f8(s, 1);
    r = func_ov110_0229c388(s, s->a);
    switch (m) {
        case 0x1d:
        case 0x1e:
            if (r == 0) {
                func_0206fc4c(0);
                break;
            }
            func_0206fc4c(1);
            func_0206faf8(s->a);
            break;
        case 0x1f:
            for (i = 0; i < 15; i++) {
                if (s->a[i] == 0xfff1) {
                    continue;
                }
                for (j = 0; j < 15; j++) {
                    if (s->a[i] == s->b[j]) {
                        s->b[j] = 0xfff1;
                        j = 15;
                    }
                }
            }
            r = func_ov110_0229c388(s, s->b);
            if (r == 0) {
                func_0206fc4c(0);
                break;
            }
            func_0206fc4c(1);
            func_0206fc80((unsigned char) r);
            func_0206faf8(s->b);
            MI_CpuCopy8(s->a, data_021f3a68, 0x1e);
            func_ov110_0229c324(s, 3);
            break;
        case 0x20:
            MI_CpuCopy8(s->a, data_021f3a86, 0x1e);
            func_ov110_0229c324(s, 4);
            func_0206fc4c(1);
            break;
    }
}
