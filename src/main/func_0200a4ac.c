/* func_0200a4ac @ 0x0200a4ac, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
    int unk_08;
    int unk_0C;
} Struct0200A4AC;

void func_0200a4ac(Struct0200A4AC *ptr, int a, unsigned char b, int c, int d)
{
    ptr->unk_00 = a;
    ptr->unk_04 = b;
    ptr->unk_08 = c;
    ptr->unk_0C = d;
}
