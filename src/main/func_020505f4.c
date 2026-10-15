/* func_020505f4 @ 0x020505f4, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020dcd78;
extern char *data_021c8184;

extern int func_020044a0(void *);
extern void func_0205502c(void *);
extern void func_0209d090(void *);
extern int func_02055454(void *);
extern void func_0209d200(void *, void *);

typedef struct UnkStruct_020505f4 {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    char pad_50[0x98 - 0x50];
    char unk_98[0x16c - 0x98];
} UnkStruct_020505f4;

void func_020505f4(int arg0, int arg1)
{
    char *base;
    UnkStruct_020505f4 *e;
    int v;

    if (arg1 < 0) {
        return;
    }
    if (arg1 >= data_020dcd78) {
        return;
    }
    if (data_021c8184 == 0) {
        return;
    }

    base = data_021c8184 + 0x50;
    e = (UnkStruct_020505f4 *) (base + arg1 * 0x16c);

    v = e->unk_44;
    if (v != 0 && v != 1) {
        func_020044a0(e);
    }

    e->unk_40 = -1;
    e->unk_44 = 0;

    func_0205502c(&e->unk_98);
    func_0209d090(&e->unk_4C);
    func_02055454(&e->unk_98);
    func_0209d200((void *) (arg0 + 0x600), &e->unk_48);
}
