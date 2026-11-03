/* mail_text_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203dd00 @ 0x0203dd00, 0xe bytes, Thumb
 * func_0203dcfc @ 0x0203dcfc, 0x2 bytes, Thumb
 * func_0203dcbc @ 0x0203dcbc, 0x3e bytes, Thumb
 */

typedef struct {
    char pad_00[0x45];
    unsigned char unk_45;
    unsigned int unk_48;
    unsigned int unk_4C;
} UnkStruct_0203dd00;

struct UnkStruct_0203dcbc {
    char pad_00[4];
    int unk_04;
    char pad_08[52];
    int unk_3C;
    char pad_40[5];
    unsigned char flag45;
    char pad_46[2];
    int unk_48;
};

extern int func_02050bdc_unk(int);
extern void func_0203dba0(struct UnkStruct_0203dcbc *);
extern void func_020a9318(struct UnkStruct_0203dcbc *);

void func_0203dd00(UnkStruct_0203dd00 *arg)
{
    arg->unk_45 = 0;
    arg->unk_48 = 0;
    arg->unk_4C = 0;
}

void func_0203dcfc(void) {}

void func_0203dcbc(struct UnkStruct_0203dcbc *p, int value)
{
    if (p->flag45) {
        p->unk_3C = func_02050bdc_unk(value);
        p->flag45 = 0;
    } else {
        p->unk_3C = value;
    }
    func_0203dba0(p);
    if (p->unk_04 == p->unk_48) {
        p->unk_48 = 0;
        func_020a9318(p);
    }
}
