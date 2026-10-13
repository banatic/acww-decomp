/* func_020325b8 @ 0x020325b8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    short unk_28;
    short unk_2A;
    int unk_2C;
} UnkStruct_020325b8;
extern void func_0202f8fc(unsigned char *b, int a, int c);
void func_020325b8(UnkStruct_020325b8 *p)
{
    int *a;
    unsigned char *b;
    int i;
    i = 0;
    p->unk_2A = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_10 = 0;
    p->unk_14 = 0;
    p->unk_18 = 0;
    p->unk_1C = 0x1000;
    p->unk_20 = 0x1000;
    p->unk_24 = 0x1000;
    p->unk_28 = 0;
    p->unk_2C = 0;
    *((unsigned char *) p + 0x98) = 0;
    a = (int *) ((unsigned char *) p + 0x30);
    b = (unsigned char *) p + 0x60;
    for (; i < 4; i++) {
        a[0] = 0;
        a[1] = 0;
        a[2] = 0;
        func_0202f8fc(b, 0, 0);
        a += 3;
        b += 8;
    }
}
