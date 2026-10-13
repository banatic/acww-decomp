/* func_ov004_02245bb8 @ 0x02245bb8, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    unsigned short unk_00, unk_02;
} UnkStruct_02245bb8;

extern int func_0208ff98(void);
extern int func_020b6590(void);
extern int func_020b755c(int a, void *b, int *c, unsigned char *d);
extern void func_ov004_02245cf4(void *self, int i);
extern int func_ov004_02230d94(void);
extern void func_0208ffcc(void);

extern unsigned char data_020ccf94[];
extern unsigned char data_021c75b8;
extern unsigned char data_021f6c34;
extern unsigned char data_021f6c38;
extern unsigned char data_021fbe40[];

void func_ov004_02245bb8(void *self)
{
    char a[0x10];
    int b;
    unsigned char c;
    int f;
    unsigned char v;
    UnkStruct_02245bb8 *w;

    f = (data_021c75b8 == 2) ? 1 : 0;
    if (f == 0) {
        return;
    }
    if (func_0208ff98() != 0) {
        f = (data_021f6c38 != 0 && data_021f6c34 != 0) ? 1 : 0;
        if (f != 0) {
            if (func_020b755c(func_020b6590(), a, &b, &c) != 0) {
                if (b == 1) {
                    v = c;
                    (*(int **) data_020ccf94)[0x1a] = v;
                    *((unsigned char *) self + 0x31c) = v;
                    func_ov004_02245cf4(self, 3);
                    return;
                }
            }
        }
    }
    if (func_ov004_02230d94() != 0) {
        func_ov004_02245cf4(self, 0);
    } else {
        w = (UnkStruct_02245bb8 *) data_021fbe40;
        if ((w->unk_02 & 0xff3) != 0) {
            func_0208ffcc();
            func_ov004_02245cf4(self, 2);
        }
    }
}
