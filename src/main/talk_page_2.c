/* talk_page_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206c604 @ 0x0206c604, 0x6 bytes, Thumb
 * func_0206c5fc @ 0x0206c5fc, 0x6 bytes, Thumb
 * func_0206c5f4 @ 0x0206c5f4, 0x8 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[80];
    unsigned long unk_50;
} UnkStruct_0206c604;

typedef struct {
    unsigned char pad_00[80];
    unsigned long unk_50;
} UnkStruct_0206c5fc;

extern void func_0206d424(void);

void func_0206c604(UnkStruct_0206c604 *p)
{
    p->unk_50 = 1;
}

void func_0206c5fc(UnkStruct_0206c5fc *p)
{
    p->unk_50 = 2;
}

void func_0206c5f4(void)
{
    func_0206d424();
}
