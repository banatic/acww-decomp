/* func_02003c38 @ 0x02003c38, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
} UnkStruct_02003c38;

extern int func_0206fd04(void);
extern int func_0206fd10(void);
extern const char data_020c7588;

void func_02003c38(UnkStruct_02003c38 *p)
{
    int a;
    int b;

    a = func_0206fd04() != 0;
    b = func_0206fd10();
    if (p->unk_10 > 0) {
        p->unk_10--;
    }
    if (p->unk_14) {
        if (p->unk_0C == 0x1000 && b < 0x1000) {
            p->unk_10 = 0x17;
        }
    } else if (a) {
        p->unk_08 = 0;
        p->unk_04 = data_020c7588;
        p->unk_10 = 0xe;
    }
    p->unk_14 = a;
    p->unk_0C = b;
}
