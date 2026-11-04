/* local_wireless_7: 3 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02266908 @ 0x02266908, 0x48 bytes, ARM
 * func_ov066_022668c4 @ 0x022668c4, 0x44 bytes, ARM
 * func_ov066_0226686c @ 0x0226686c, 0x58 bytes, ARM
 */

typedef struct {
    int unk_00;
    unsigned int unk_04;
    unsigned char pad_08[0x34];
    unsigned int unk_3C;
} Obj066;

extern int (*data_ov066_0226bde8)(int a, int b);
extern int (*data_ov066_0226bde4)(int);
extern volatile Obj066 *data_ov066_0226bdec;
extern void (*data_ov066_0226bde0)(int);

void func_ov066_0226686c(int arg);

int func_ov066_02266908(int a, int b)
{
    if (data_ov066_0226bde8) {
        int r = data_ov066_0226bde8(a, b);
        if (r) {
            return r;
        }
    }
    func_ov066_0226686c(0x42);
    return 0;
}

void func_ov066_022668c4(void *p)
{
    if (data_ov066_0226bde4 == 0) {
        return;
    }
    if (p == 0) {
        return;
    }
    data_ov066_0226bde4((int) p);
}

void func_ov066_0226686c(int arg)
{
    data_ov066_0226bdec->unk_04 = arg | 0x80;
    data_ov066_0226bdec->unk_3C &= ~0x800;
    if (data_ov066_0226bde0) {
        data_ov066_0226bde0(arg);
    }
}
