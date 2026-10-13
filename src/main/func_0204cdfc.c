/* func_0204cdfc @ 0x0204cdfc, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *p);
extern void func_0204cc24(void *p);
extern void func_0204cc14(void *p);
extern void func_0204cbe0(void *p);

struct Elem {
    unsigned char unk_00, unk_01, unk_02, unk_03;
};

struct UnkStruct_0204cdfc {
    void *unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    char pad_0C[0x15];
    signed char unk_21;
    char pad_22[0x32];
    unsigned char unk_54;
    unsigned char unk_55;
    unsigned char unk_56;
    unsigned char unk_57;
    struct Elem arr[4];
};

void func_0204cdfc(struct UnkStruct_0204cdfc *p)
{
    unsigned char zero;
    unsigned char one;
    struct Elem *q;
    int i;

    func_0209df64(p);

    p->unk_04 = 0;
    p->unk_08 = 1;
    p->unk_09 = 1;
    p->unk_0A = 0;
    p->unk_0B = 0;

    func_0204cc24(p);
    func_0204cc14(p);
    func_0204cbe0(p);

    zero = 0;
    one = 1;
    q = p->arr;
    for (i = 0; i < 4; i++) {
        q->unk_00 = one;
        q->unk_01 = one;
        q->unk_02 = zero;
        q->unk_03 = zero;
        q++;
    }

    p->unk_21 = -1;
    p->unk_54 = one;
    p->unk_55 = one;
    p->unk_56 = zero;
    p->unk_57 = zero;
}
