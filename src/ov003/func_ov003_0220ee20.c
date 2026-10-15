/* func_ov003_0220ee20 @ 0x0220ee20, 0xfc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c526c;

typedef struct {
    char pad_00[0x7d4];
    unsigned char flag;
    char pad_7D5[0x7f0 - 0x7d4 - 1];
    unsigned int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    unsigned int unk_7FC;
} UnkStruct_0220ee20;

extern int func_02056f94(void *p);
extern void func_020109fc(void *p, int a, int b, int c);
extern int func_0200faf0(void *p, int x);
extern void func_02035a70(void *p);
extern void func_0200f3e8(void *p);
extern int func_0203e110(void);
extern int func_02008258(void *p, int v);
extern void func_020110c4(void *buf, void *p);
extern int func_0204bcdc(void *buf);
extern int func_0204bc64(void *p);
extern int func_ov003_02217c5c(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_0200d4e8(void *p, int a, int b, int c);
extern unsigned int *func_0200f27c(void *p, int a);

void func_ov003_0220ee20(void *self)
{
    UnkStruct_0220ee20 *s = (UnkStruct_0220ee20 *) self;
    unsigned char *flagp = &s->flag;
    int res;
    unsigned short buf[2];

    if (func_02056f94((char *) self + 0x2d0)) {
        *flagp = 1;
        func_020109fc(self, 1, 3, 0);
    }
    if (*flagp) {
        if (func_0200faf0(self, 0x59a)) {
            func_02035a70((char *) data_021c526c + 0x2e4);
            func_0200f3e8(self);
            func_0203e110();
            s->unk_7FC = func_02008258(self, s->unk_7F0);
            func_020110c4(buf, self);
            if (func_0204bcdc(buf)) {
                buf[1] = 0xfff1;
                res = (func_0204bc64(buf) == func_0204bc64(&buf[1])) ? 1 : 0;
            } else {
                res = (buf[0] == 0xfff1) ? 1 : 0;
            }
            if (res == 0) {
                func_ov003_02217c5c(self, 2, 2, 0, 0, 0, 6, -1);
            } else {
                func_0200d4e8(self, 3, 1, -1);
                func_0200f27c(self, 0);
            }
        }
    }
}
