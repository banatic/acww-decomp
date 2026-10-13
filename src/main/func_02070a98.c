/* func_02070a98 @ 0x02070a98, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *p1, void *field, int a, int b);
extern int func_020a9034(int a, int b, int c);
extern void func_02070b24(void *p1, int a, unsigned char b, unsigned char c);

typedef struct {
    char pad_00[0x68];
    void *unk_68;
} UnkStruct_02070a98;

typedef struct {
    char pad_00[0x28];
    unsigned int unk_28;
} UnkStruct_02070a98_2;

extern unsigned char data_021c828c[];

void func_02070a98(UnkStruct_02070a98 *p1, int p2, int p3, int p4, unsigned char p5, unsigned char p6)
{
    if (p1->unk_68 != 0) {
        func_02070b84(p1, p1->unk_68, p3, p4);
    }
    p1->unk_68 = (void *) func_020a9034(p3, p4, 1);
    func_02070b24(p1, p2, p5, p6);
    ((UnkStruct_02070a98_2 *) p1->unk_68)->unk_28 = (unsigned int) data_021c828c;
}
