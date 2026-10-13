/* func_02041c28 @ 0x02041c28, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02038a44(void);
extern int func_020e88dc(void *, int, int);

struct GlobalData {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char pad[6];
    int n;
};
extern struct GlobalData data_021c75b8;
extern int data_021c75bc;

typedef void (*Handler)(void);
struct HandlerEntry {
    Handler handler;
    char pad[12];
};
extern struct HandlerEntry data_020ca51c[];

void func_02041c28(void)
{
    unsigned char c1;
    unsigned char c0;
    int n;
    int flag;

    if (func_02038a44() != 0) {
        return;
    }
    c1 = data_021c75b8.unk_01;
    c0 = data_021c75b8.unk_00;
    if (c0 == 0 || c0 == 2) {
        return;
    }
    n = data_021c75b8.n;
    if (n != 0) {
        if (n >= 0) {
            flag = 0x1000;
        } else {
            flag = 0;
        }
        if (n < 0) {
            n = -n;
        }
        if (func_020e88dc(&data_021c75bc, flag, n) != 0) {
            data_021c75b8.n = 0;
        }
    }
    if (data_020ca51c[c1].handler != 0) {
        data_020ca51c[c1].handler();
    }
}
