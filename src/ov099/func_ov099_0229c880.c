/* func_ov099_0229c880 @ 0x0229c880, 0x78 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xcc];
    char sub[1];
    char pad_CD[0x2900 - 0xcc - 1];
    unsigned short unk_2900;
    unsigned char unk_2902;
    unsigned char unk_2903;
} UnkStruct_0229c880;

extern int func_ov099_0229cf30(void *a, int b);
extern int func_ov099_0229cf04(void *a, int b);
extern int func_ov094_0229aaac(void *a, int b);
extern int func_ov094_0229aa84(void *a, int b);
extern void func_ov094_0229aa58(void *a, int b);
extern void func_ov094_0229a99c(void *a, unsigned short c, unsigned char d);
extern int func_ov099_0229cf20(void *a, int b);

void func_ov099_0229c880(UnkStruct_0229c880 *s, int param1)
{
    if (func_ov099_0229cf30(s, param1)) {
        int ret1 = func_ov099_0229cf04(s, param1);
        s->unk_2903 = 2;
        s->unk_2900 = func_ov094_0229aaac(&s->sub, ret1);
        s->unk_2902 = func_ov094_0229aa84(&s->sub, ret1);
        func_ov094_0229aa58(&s->sub, ret1);
        func_ov094_0229a99c(&s->sub, s->unk_2900, s->unk_2902);
    } else {
        if (func_ov099_0229cf20(s, param1) == 0) {
            return;
        }
    }
}
