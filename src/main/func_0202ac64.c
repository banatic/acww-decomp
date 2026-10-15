/* func_0202ac64 @ 0x0202ac64, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern struct Global data_020c8b18;

struct UnkStruct_0202ac64 {
    unsigned char pad_00[0x824];
    unsigned char flag;
    unsigned char pad_825[0xb];
    int value;
};

struct Main {
    unsigned char pad_00[0x100];
    struct UnkStruct_0202ac64 *sub;
    char buf[0x1e];
    unsigned char byte;
};

struct UnkStruct_0202ac64_2 {
    void *ptr;
    unsigned char byte;
};

struct Global {
    int value;
    unsigned char byte;
};

void func_0202ac64(struct Main *a, struct UnkStruct_0202ac64_2 *b)
{
    struct UnkStruct_0202ac64 *p;
    int arg5, arg6, arg7, arg8, arg9;

    p = a->sub;
    arg5 = func_020036e8(func_0208150c(p->value));
    arg6 = data_020c8b18.value;
    arg7 = 5;
    arg8 = p->flag & 1;
    arg9 = data_020c8b18.byte;

    func_0202da38(a, a->buf, &a->byte, 0x1e, arg5, arg6, arg7, arg8, arg9);

    a->byte += 7;
    b->ptr = a->buf;
    b->byte = a->byte;
    a->sub->flag = (a->sub->flag + 1) & 1;
}
