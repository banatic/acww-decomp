/* screen_panels: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208b090 @ 0x0208b090, 0x48 bytes, Thumb
 * func_0208b034 @ 0x0208b034, 0x5c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad_08[0x34a - 0x8];
    unsigned char unk_34A;
} UnkStruct_0208b034;

extern int func_02011ed4(void);
extern int func_02011f3c(void);
extern void func_0208b2b0(int);
extern void func_0208b344(int);
extern void func_0208b22c(int);
extern void func_0208b1d4(int);
extern void func_0208b374(int);
extern int func_0208ffac(void);
extern int func_0208ff98(void);
extern void func_02011f54(int, int, int);

void func_0208b090(int param)
{
    int result;

    result = func_02011ed4();
    if (result == 1) {
        if (func_02011f3c() != 0) {
            func_0208b2b0(param);
        } else {
            func_0208b344(param);
        }
    } else if (result == 2) {
        func_0208b22c(param);
    } else if (result == 3) {
        func_0208b1d4(param);
    } else {
        func_0208b374(param);
    }
}

void func_0208b034(UnkStruct_0208b034 *p)
{
    int flag = 0;

    if (p->unk_34A != 0) {
        if (func_0208ffac() != 0) {
            flag = 1;
        }
    } else {
        if (func_0208ff98() != 0) {
            flag = 1;
        }
    }

    if (flag == 0) {
        return;
    }

    p->unk_34A = (p->unk_34A == 0) ? 1 : 0;

    if (p->unk_04 == 3) {
        func_02011f54(p->unk_34A, 1, 1);
    }
}
