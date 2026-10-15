/* func_ov068_0226831c @ 0x0226831c, 0xf0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *p, int v);
extern int func_02056f94(void *p);
extern int func_02019c20(void *p, int a, int b, int c, unsigned short d, int e);
extern int func_02034270(void *out, const void *in, int a, int b);
extern int func_ov003_02221228(int a, const void *b);
extern int func_02091254(int a, const void *b, int c, int d);
extern int func_0200442c(void *p, int a, int b, int c);
extern void func_0201233c(void *p, unsigned short a, int b);
extern void func_02016638(void *p, void *q, void *r, int a, int b);
extern void func_0203423c(void *p);

extern volatile unsigned short data_020c80f8;

struct UnkStruct_0226831c {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned char pad_68[0x188 - 0x68];
    unsigned char unk_188;
    unsigned char pad_189[0x334 - 0x189];
    unsigned char unk_334;
    unsigned char pad_335[0x514 - 0x335];
    unsigned char unk_514;
    unsigned char pad_515[0x564 - 0x515];
    unsigned char unk_564;
    unsigned char pad_565[0x9b4 - 0x565];
    unsigned char unk_9B4;
};

struct UnkStruct_0226831c_2 {
    unsigned char pad_00[0x1c];
    unsigned char mode;
};

void func_ov068_0226831c(struct UnkStruct_0226831c_2 *obj, struct UnkStruct_0226831c *s)
{
    unsigned short h;
    unsigned int vec[3];
    unsigned int matrix[16];
    unsigned int vec2[3];
    int r;
    unsigned int *vp;

    if (func_020164a0(&s->unk_334, 0) != 0x127) {
        return;
    }
    if (func_02056f94(&s->unk_188) == 0) {
        return;
    }

    h = data_020c80f8;
    func_02019c20(&s->unk_564, 1, 0x128, 1, h, 0);

    vp = &s->unk_5C;
    vec[0] = s->unk_5C;
    vec[1] = vp[1];
    vec[2] = vp[2];

    func_02034270(matrix, vec, 0, 0);
    r = matrix[13];

    vec2[0] = vec[0];
    vec2[1] = vec[1];
    vec2[2] = vec[2];
    func_ov003_02221228(0, vec2);

    if (r == 0x13) {
        func_02091254(0x8f, vec, 0, 0);
    } else {
        func_02091254(0x8e, vec, 0, 0);
    }

    func_0200442c(&s->unk_514, 0x7e8, 0x7f, 0);
    func_0201233c(&s->unk_9B4, h, 1);
    func_02016638(&s->unk_334, s, &s->unk_9B4, 0x128, 3);

    obj->mode = 2;
    func_0203423c(matrix);
}
