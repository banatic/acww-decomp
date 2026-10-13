/* func_020249cc @ 0x020249cc, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);

struct InputA {
    char pad_00[0x100];
    void *ptr;
    char arr[0x1E];
    unsigned char byte;
};

struct UnkStruct_020249cc {
    char pad_00[0x830];
    int value;
};

struct Output {
    void *ptr;
    unsigned char byte;
};

struct GlobalData {
    int unk_00;
    unsigned char unk_04;
};

extern struct GlobalData data_020c8c60;

void func_020249cc(struct InputA *arg0, struct Output *out)
{
    int sp0, sp4, sp8, sp12, sp16;

    sp0 = func_020036e8(func_0208150c(((struct UnkStruct_020249cc *) (arg0->ptr))->value));
    sp4 = data_020c8c60.unk_00;
    sp8 = data_020c8c60.unk_04;
    sp12 = 0;
    sp16 = 0;
    func_0202da38(arg0, arg0->arr, &arg0->byte, 0x1e, sp0, sp4, sp8, sp12, sp16);
    out->ptr = (void *) ((char *) arg0 + 0x104);
    out->byte = arg0->byte;
}
