/* func_020b90cc @ 0x020b90cc, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xcc];
    char unk_CC[0x14];
    int unk_E0;
    char pad_E4[1];
    unsigned char unk_E5;
    unsigned char unk_E6;
} UnkStruct_020b90cc;

extern void *func_0208a1d0(char *p);
extern void *func_0208a840(UnkStruct_020b90cc *self);
extern int func_0208a824(UnkStruct_020b90cc *self);
extern int func_0208a80c(UnkStruct_020b90cc *self);
extern int func_0208a1b0(void *p, int k);
extern int func_0208a198(void *p, int k);
extern void func_02088df8(int z, void *p, int a, int b, int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8);
extern void func_0208ab3c(UnkStruct_020b90cc *self);

void func_020b90cc(UnkStruct_020b90cc *self)
{
    int ok;
    int a;
    int s;
    void *p;
    void *q;
    int r;

    ok = 0;
    if (self->unk_E0 < 0x19) {
        if (self->unk_E5 != 0) {
            p = func_0208a1d0(self->unk_CC);
            q = func_0208a840(self);
            a = func_0208a824(self);
            s = func_0208a80c(self);
            r = func_0208a1b0(q, -1);
            a = a + r + func_0208a1b0(self->unk_CC, -1);
            r = func_0208a198(q, -1);
            s = s + r + func_0208a198(self->unk_CC, -1);
            func_02088df8(0, p, a, s, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
            ok = 1;
        }
        func_0208ab3c(self);
    }
    self->unk_E6 = (unsigned char) ok;
}
