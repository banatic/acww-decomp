/* func_ov096_022a18dc @ 0x022a18dc, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022a18dc {
    char pad_00[0x8c];
    char unk_8C;
};

extern int func_020ee45c(struct UnkStruct_022a18dc *s);
extern void func_ov090_022993cc(int x, unsigned char b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov096_0229c414(struct UnkStruct_022a18dc *s);
extern void func_ov096_0229c2dc(struct UnkStruct_022a18dc *s, int x);

int func_ov096_022a18dc(struct UnkStruct_022a18dc *s, int b)
{
    int x;

    x = func_020ee45c(s);
    if (b == -1) {
        goto fail;
    }
    if (b == 0) {
        goto fail;
    }

    func_ov090_022993cc(x, (unsigned char) b);
    s->unk_8C = 5;
    func_ov002_022080a0((void *) (s), 1);
    if (b != 7) {
        func_ov096_0229c414(s);
    }
    func_ov096_0229c2dc(s, 0x80);
    return 1;

fail:
    return 0;
}
