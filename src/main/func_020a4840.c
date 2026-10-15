/* func_020a4840 @ 0x020a4840, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a4840 {
    char pad_00[0xa1];
    unsigned char state;
};

struct Buf {
    char pad_00[0x24];
};

extern unsigned char data_021dc7a8[];
extern int data_021dc7bc;
extern int data_021f3c34;
extern int data_020e3c54;

extern int func_020682e0(int a);
extern void *func_02098844(int *p, int v);
extern void *func_02094fd4(struct Buf *b);
extern void *func_02099870(void *p);
extern void *func_02095074(void *p, struct Buf *b);
extern void func_02068404(int a, int b, struct Buf *c);
extern void func_02099a38(void *p);
extern void func_0209ef10(unsigned char *p, int v);
extern int func_020a1954(struct UnkStruct_020a4840 *o, int *p, int n);
extern int func_02098880(int *p);
extern void *func_02094fbc(struct Buf *b);

void func_020a4840(struct UnkStruct_020a4840 *self)
{
    struct Buf buf;
    unsigned char *base;
    int h;
    void *f;

    h = func_020682e0(0);
    base = data_021dc7a8;
    f = func_02098844(&data_021dc7bc, data_021f3c34);
    func_02094fd4(&buf);
    func_02095074(func_02099870(f), &buf);
    func_02068404(h, 0, &buf);
    func_02099a38(f);
    func_0209ef10(base, data_021f3c34);
    func_020a1954(self, &data_020e3c54, 7);
    if (func_02098880(&data_021dc7bc) == 0) {
        base[0x17276] = 0;
    }
    self->state = 0;
    func_02094fbc(&buf);
}
