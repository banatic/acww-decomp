/* func_ov050_022627d4 @ 0x022627d4, 0x7c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x70];
    unsigned char *unk_B4;
    char pad_B8[0x18];
    int unk_D0;
} UnkStruct_022627d4;

typedef struct {
    int data[9];
} Local2;

extern int func_0209ad9c(void *arg, int value);
extern int func_0209b4d4(void *object);
extern void *func_02094fd4(void *arg);
extern void func_0209bb90(int arg, int value);
extern int func_02099fe8(void);
extern void func_0209a934(void *arg);
extern int func_0209ac50(void *arg1, void *arg2, unsigned short *arg3);
extern void func_02068404(int arg1, int arg2, void *arg3);
extern void *func_02094fbc(void *arg);

void func_ov050_022627d4(UnkStruct_022627d4 *a, void *b)
{
    unsigned short local1;
    Local2 local2;
    int r6;

    r6 = func_0209b4d4((void *) (func_0209ad9c(b, 0)));
    func_02094fd4(&local2);
    func_0209bb90(r6, 2);
    a->unk_B4[0x73e] = 0;
    if (func_02099fe8() >= 0) {
        func_0209a934(b);
        local1 = 0x1561;
        func_0209ac50(b, &local2, &local1);
        func_02068404(a->unk_40, 1, &local2);
        a->unk_D0 = 0x29;
    } else {
        a->unk_D0 = 0x17;
    }
    func_02094fbc(&local2);
}
