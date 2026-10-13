/* func_ov050_02262970 @ 0x02262970, 0x7c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x70];
    char *unk_B4;
    char pad_B8[0x18];
    int unk_D0;
} UnkStruct_02262970;

extern int func_0209ad9c(int, int);
extern int func_0209b4d4(int);
extern int func_0209bb90(int, int);
extern int func_02099fe8(int);
extern void func_0209aacc(int);
extern int func_0209b4cc(int, int);
extern void func_02094fd4(void *);
extern void func_02003618(int, void *);
extern void func_02068404(int, int, void *);
extern void func_02094fbc(void *);

void func_ov050_02262970(UnkStruct_02262970 *self, int arg1)
{
    char buf[0x20];
    int v;

    v = func_0209ad9c(arg1, 0);
    if (func_02099fe8(func_0209bb90(func_0209b4d4(v), 1)) >= 0) {
        func_0209aacc(arg1);
        v = func_0209b4cc(v, 1);
        if (v != 0) {
            func_02094fd4(buf);
            func_02003618(v, buf);
            func_02068404(self->unk_40, 0, buf);
            func_02094fbc(buf);
        }
        self->unk_B4[0x73e] = 0;
        self->unk_D0 = 0x1f;
    } else {
        self->unk_D0 = 0x17;
    }
}
