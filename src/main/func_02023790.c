/* func_02023790 @ 0x02023790, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02023790 {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[30];
    unsigned char unk_122;
};

struct Output {
    void *ptr;
    unsigned char byte;
};

struct GlobalData {
    int unk_00;
    unsigned char unk_04;
};

extern struct GlobalData data_020c89a8;
extern void func_0208150c(int);
extern int func_020036e8(void);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);

void func_02023790(struct UnkStruct_02023790 *p, struct Output *out)
{
    unsigned char b;
    int result;
    int c;

    b = ((unsigned char *) &data_020c89a8)[4];
    func_0208150c(*(int *) ((char *) p->unk_100 + 0x830));
    result = func_020036e8();
    c = *(int *) &data_020c89a8;
    func_0202da38(p, p->unk_104, &p->unk_122, 30, result, c, b, 2, b);
    out->ptr = p->unk_104;
    out->byte = p->unk_122;
}
