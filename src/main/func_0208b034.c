/* func_0208b034 @ 0x0208b034, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208ffac(void);
extern int func_0208ff98(void);
extern void func_02011f54(int, int, int);

typedef struct {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad_08[0x34a - 0x8];
    unsigned char unk_34A;
} UnkStruct_0208b034;

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
