/* func_ov003_022190b0 @ 0x022190b0, 0x110 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[5];
    unsigned char st;
} UnkStruct_022190b0;

extern int func_02056f28(void *, int);
extern void func_0200f328(void *, int);
extern int func_02056f94(void *);
extern void func_ov003_022195ac(void *, int);
extern unsigned int func_ov003_022195a8(void *);
extern int func_02073908(int, int);
extern void func_0209129c(int);
extern void func_020109a0(void *, int, int, int);
extern void func_0200c9a8(void *, int, int, int);
extern int data_020ccf94;

void func_ov003_022190b0(char *a)
{
    UnkStruct_022190b0 *p = (UnkStruct_022190b0 *) (a + 0x7d4);
    void *q = a + 0x8f0;
    unsigned char *st = &p->st;

    switch (p->st) {
        case 0:
            if (func_02056f28(a + 0x2d0, 0xa)) {
                func_0200f328(a, 0x63);
            } else if (func_02056f28(a + 0x2d0, 0x19)) {
                func_0200f328(a, 0x7f2);
            }
            if (func_02056f94(a + 0x2d0)) {
                *st = 1;
                func_ov003_022195ac(q, 1);
            }
            break;
        case 1:
            if (func_02073908(data_020ccf94, *(int *) (a + 0x800)) == 0) {
                if (func_ov003_022195a8(q) >= 2) {
                    *st = 2;
                }
            }
            break;
        case 2:
            if (p->unk_04 > -1) {
                func_0209129c(p->unk_04);
            }
            if (func_02073908(data_020ccf94, *(int *) (a + 0x800)) != 0) {
                func_ov003_022195ac(q, 2);
            }
            func_020109a0(a, 0xa0, 3, 0);
            func_0200f328(a, 0x7f1);
            *st = 3;
            break;
        case 3:
            if (func_02056f94(a + 0x2d0)) {
                func_0200c9a8(a, 3, 5, -1);
            }
            break;
    }
}
