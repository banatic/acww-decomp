/* func_02022bbc @ 0x02022bbc, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207f1c8(int);
extern void *func_0209b5ec(void *);
extern int func_0209c330(unsigned char *);
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, char *, char *, int, int, int, int, int, int);

struct Inner_02022bbc {
    char pad_00[0x830];
    int unk_830;
};

struct Outer_02022bbc {
    char pad_00[0x100];
    struct Inner_02022bbc *inner;
};

struct Arg2_02022bbc {
    int unk_00;
    unsigned char unk_04;
};

void func_02022bbc(struct Outer_02022bbc *a0, int arg1, struct Arg2_02022bbc *arg2)
{
    int flag;
    int ret;

    flag = (arg1 != func_0209c330((unsigned char *) func_0209b5ec((void *) func_0207f1c8(a0->inner->unk_830)))) ? 1 : 0;

    ret = func_020036e8((unsigned char *) func_0208150c(a0->inner->unk_830));

    func_0202da38(a0, (char *) a0 + 0x104, (char *) a0 + 0x122, 0x1e, ret, arg2->unk_00, arg2->unk_04, flag, 0);
}
