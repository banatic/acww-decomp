/* func_ov100_0229c3c0 @ 0x0229c3c0, 0x12c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x28dc];
    unsigned short a[15];
    unsigned short b[15];
    char pad_2918[0x2928 - 0x2918];
    unsigned char st;
} UnkStruct_0229c3c0;

extern void func_ov100_0229c2a0(UnkStruct_0229c3c0 *, int);
extern void RtcSendPxiCommand(int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov100_0229c56c(UnkStruct_0229c3c0 *, int);
extern int func_ov100_0229c390(UnkStruct_0229c3c0 *, unsigned short *);
extern int func_0206fca4(void);
extern void func_0206fc4c(int);
extern void func_0206faf8(unsigned short *);
extern void func_0206fc80(int);
extern void func_ov100_0229c324(UnkStruct_0229c3c0 *, int);
extern void MI_CpuCopy8(void *, const void *, int);
extern const unsigned short data_021f3a68[];
extern const unsigned short data_021f3a86[];

void func_ov100_0229c3c0(UnkStruct_0229c3c0 *s)
{
    int r;
    int i, j;

    func_ov100_0229c2a0(s, 8);
    RtcSendPxiCommand(0x27);
    s->st = 5;
    func_ov002_02208098((void *) (s), 0x15);
    func_ov100_0229c56c(s, 1);
    r = func_ov100_0229c390(s, s->a);
    switch (func_0206fca4()) {
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
                    unsigned short *bp = (unsigned short *) ((char *) s + 2 * j + 0x28fa);
                    if (s->a[i] == s->b[j]) {
                        *bp = 0xfff1;
                        j = 15;
                    }
                }
            }
            r = func_ov100_0229c390(s, s->b);
            if (r == 0) {
                func_0206fc4c(0);
                break;
            }
            func_0206fc4c(1);
            func_0206fc80((unsigned char) r);
            func_0206faf8(s->b);
            MI_CpuCopy8(s->a, data_021f3a68, 0x1e);
            func_ov100_0229c324(s, 3);
            break;
        case 0x20:
            MI_CpuCopy8(s->a, data_021f3a86, 0x1e);
            func_ov100_0229c324(s, 4);
            func_0206fc4c(1);
            break;
    }
}
