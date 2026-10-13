/* func_02046830 @ 0x02046830, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02046830;

extern UnkStruct_02046830 *func_0204e414(void);
extern void func_0209dfa4(int);
extern void func_0204a848(char *addr, UnkStruct_02046830 *arg1, int x, int y);
extern void func_02046f14(char *a, UnkStruct_02046830 *b);
extern void func_0204695c(void);
extern void func_02046bc8(void);
extern int func_02073d90(unsigned int);
extern int func_02046904(void);
extern void func_02046c2c(char *);
extern int func_020b65c4(void);
extern void func_0204763c(char *, int);
extern void func_02046a74(int);
extern void func_02042c40(char *);
extern void func_02045b3c(char *);
extern void func_02042c28(char *);
extern void func_02042f08(char *);

extern char data_021c7a08[];
extern char data_021c779c[];
extern char data_021c7c48[];
extern char data_021c7880[];
extern char data_021c7788[];
extern char data_021c80b4[];
extern unsigned int data_020ccf94;

void func_02046830(void)
{
    UnkStruct_02046830 *r6;
    int width, height;
    char *p;
    int outer;
    int inner;
    int tmp;

    r6 = func_0204e414();
    func_0209dfa4(0);
    if (r6 != 0) {
        width = r6->unk_04 - 2;
        height = r6->unk_08 - 2;
        inner = 0;
        for (outer = 0; outer < width; outer++) {
            tmp = inner;
            p = (char *) data_021c7a08 + outer * 0x90;
            for (; tmp < height; tmp++) {
                func_0204a848(p + tmp * 0x24, r6, outer + 1, tmp + 1);
            }
        }
        func_02046f14(data_021c779c, r6);
    }
    func_0204695c();
    func_02046bc8();
    if (func_02073d90(data_020ccf94) == 0) {
        if (func_02046904() != 0) {
            func_02046c2c(data_021c779c);
        }
        if (func_020b65c4() == 0x3f) {
            func_0204763c(data_021c779c, 1);
        } else {
            func_02046a74(1);
        }
    }
    func_02042c40(data_021c7c48);
    func_02045b3c(data_021c7880);
    func_02042c28(data_021c7788);
    func_02042f08(data_021c80b4);
}
