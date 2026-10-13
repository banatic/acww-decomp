/* func_020ab0a4 @ 0x020ab0a4, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0x18];
    int unk_20;
} Param;

extern int func_020a806c(int *a, int *b);
extern int func_020ac148(int a, int b, int c);
extern int func_020ab510(int a);
extern void RtcSendPxiCommand(int cmd);
extern void func_020aaee8(Param *p);

int func_020ab0a4(Param *param)
{
    int r6 = 0;
    int localA, localB;
    if (func_020a806c(&localA, &localB)) {
        int r4;
        r4 = func_020ac148(param->unk_04, localA, localB);
        if (r4 >= 0) {
            int r0;
            param->unk_00 = r4;
            r6 = 1;
            r0 = func_020ab510(param->unk_20);
            if (r0 >= 0 && r0 == r4) {
                RtcSendPxiCommand(0x2a);
            } else {
                func_020aaee8(param);
            }
        }
    }
    return r6;
}
