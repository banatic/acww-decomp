/* func_ov049_02260fe4 @ 0x02260fe4, 0x7c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc6c(void *);
extern int func_020984e8(void);
extern int func_0206fc8c(void);
extern int func_020996b8(int);
extern int func_02072ba4(int);
extern int func_02072b64(int, int);
extern void func_02071d8c(int, int, int, int, int);
extern void func_0206844c(int, char *, int);
extern int data_ov049_02263298;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x6c];
    unsigned char *unk_B0;
} UnkStruct_02260fe4;

void func_ov049_02260fe4(UnkStruct_02260fe4 *self)
{
    char buf[2];
    if (func_0206fc6c(self)) {
        int a = func_020984e8();
        int b = func_0206fc8c();
        int c = func_02072b64(func_02072ba4(func_020996b8(a)), b);
        unsigned char d = self->unk_B0[0x976];
        func_02071d8c(9, c, 4, d, 1);
        buf[0] = 0x24;
        func_0206844c(self->unk_40, buf, data_ov049_02263298);
    } else {
        buf[1] = 0x22;
        func_0206844c(self->unk_40, &buf[1], data_ov049_02263298);
    }
}
