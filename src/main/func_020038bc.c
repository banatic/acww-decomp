/* func_020038bc @ 0x020038bc, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fd04(void);
extern int func_0206fd10(void);
extern void func_0200396c(void *p, int arg);
extern signed char data_020c7588[];

typedef struct {
    unsigned char pad_00[0x20];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    unsigned char unk_30;
    unsigned char pad_31[2];
    unsigned char unk_33;
} UnkStruct_020038bc;

void func_020038bc(UnkStruct_020038bc *p)
{
    int r4, r6;

    r4 = (func_0206fd04() != 0) ? 1 : 0;
    r6 = func_0206fd10();

    if (p->unk_2C > 0) {
        p->unk_2C--;
        if (p->unk_2C == 0) {
            p->unk_33 = 1;
        }
    }

    if (p->unk_30 != 0) {
        if (p->unk_28 == 0x1000) {
            if (r6 < 0x1000) {
                p->unk_2C = 0x17;
            }
        }
    } else {
        if (r4 != 0) {
            p->unk_24 = 0;
            p->unk_20 = (int) (signed char) data_020c7588[0];
            func_0200396c(p, 1);
            p->unk_2C = 0xe;
        }
    }

    p->unk_30 = r4;
    p->unk_28 = r6;
}
