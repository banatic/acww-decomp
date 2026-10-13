/* func_ov047_02260f24 @ 0x02260f24, 0xe8 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern int func_020984e8(void);
extern void func_02098ff8(int a, int b);
extern void func_02063414(void *a, int b, int c, void *d, int e, int f, int g, int h, int i, int j);
extern void func_0209a088(void *a, int b, int _x);
extern void func_02015de4(void *a, void *b, int c, int d);
extern int func_020644cc(int a);

typedef struct {
    unsigned char pad_00[0xc8];
    int unk_C8;
    unsigned char pad_CC[2];
    unsigned short unk_CE;
    int unk_D0;
} UnkStruct_02260f24;

void func_ov047_02260f24(UnkStruct_02260f24 *self)
{
    unsigned char buf[12];
    unsigned int cond;
    int a, b;

    if (func_0204bcdc(&self->unk_CE) != 0) {
        *(unsigned short *) (buf + 4) = 0xfff1;
        a = func_0204bc64(&self->unk_CE);
        b = func_0204bc64(buf + 4);
        if (a == b) {
            cond = 1;
        } else {
            cond = 0;
        }
    } else {
        if (self->unk_CE == 0xfff1) {
            cond = 1;
        } else {
            cond = 0;
        }
    }

    if (cond != 0) {
        goto end;
    }

    {
        int t = func_020984e8();
        func_02098ff8(t, 0x35);

        func_02063414(buf + 2, 0x450c, 0x34, 0, 0, 0, 1, 10, 0, 1);
        self->unk_CE = *(unsigned short *) (buf + 2);

        if (self->unk_C8 >= 0) {
            func_0209a088(&self->unk_CE, 0, self->unk_C8);
        }

        func_02015de4(self, &self->unk_CE, 0, 7);
        func_02063414(buf, 0x450c, 0x34, &self->unk_CE, 1, 0, 1, 10, 0, 1);
        func_02015de4(self, buf, 1, 7);
    }

end:
    self->unk_D0 = (unsigned char) (func_020644cc(3) + 0x1a);
}