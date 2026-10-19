/* func_02037318 @ 0x02037318, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0209dee8(void);
extern void func_0209df94(unsigned short *);
extern void func_0209def4(void *object);
extern int func_0209dedc(void);

typedef struct {
    unsigned int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
    unsigned int unk_14;
} UnkStruct_02037318;

void func_02037318(UnkStruct_02037318 *p)
{
    unsigned int tmp;
    p->unk_0C = p->unk_00;
    p->unk_10 = p->unk_04;
    p->unk_12 = p->unk_06;
    tmp = p->unk_08;
    p->unk_14 = tmp;
    p->unk_00 = func_0209dee8();
    func_0209df94(&p->unk_04);
    func_0209def4(&p->unk_06);
    p->unk_08 = func_0209dedc();
}
