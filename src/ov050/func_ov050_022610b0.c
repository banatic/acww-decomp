/* func_ov050_022610b0 @ 0x022610b0, 0x86 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b3c0(void *a, void *b, void *c);
extern void func_0201b3a4(void *a, void *b);
extern void func_020adb24(void *a);
extern void func_0206fa8c(int);

typedef struct {
    char pad_00[0x1E];
    unsigned char unk_1E;
    char pad_1F[0x95];
    void *unk_B4;
    char pad_B8[8];
    void *unk_C0;
    void *unk_C4;
    char pad_C8[8];
    int unk_D0;
} UnkStruct_022610b0;

void func_ov050_022610b0(UnkStruct_022610b0 *s, int flag)
{
    if (flag == 0) {
        int ret;
        ret = func_0201b3c0(s->unk_B4, s->unk_C4, s->unk_C0);
        switch (ret) {
            case 0:
                func_0201b3a4(s->unk_B4, s->unk_C4);
                func_020adb24(s->unk_C4);
                s->unk_D0 = 0x12;
                break;
            case 1:
                func_020adb24(s->unk_C4);
                s->unk_D0 = 0x13;
                break;
            case 2:
                s->unk_D0 = 0x5D;
                func_0206fa8c(0);
                break;
        }
    } else {
        if (s->unk_1E != 0x40) {
            func_0206fa8c(0);
        } else {
            func_0206fa8c(1);
        }
    }
}
