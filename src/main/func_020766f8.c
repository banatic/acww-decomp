/* func_020766f8 @ 0x020766f8, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int data_021e5a2c;

void func_020736bc(void *a, int *b, int c);
void func_020785a4(int *p0, unsigned char *p1, unsigned short *p2, int *p3, unsigned char *p4, int *p5);
int func_0207cec0(int *p, int v);
void func_0207f1c8(void);
int func_0209b5e8(void);
void func_0207f270(int v);
void func_020794d0(void);
void func_0209bd5c(void);
int func_020984fc(void);
int func_02099870(void);
void func_0209b9cc(int a, unsigned char b, unsigned short *c, int d, int e);

void func_020766f8(void)
{
    unsigned char b1, b2;
    unsigned short w;
    int x, y, v14;
    int r4, r5, r6, r7;
    unsigned int temp;

    b1 = 0x16;
    w = 0xfff1;
    v14 = 4;
    b2 = 0;

    func_020736bc(data_020ccf94, &x, v14);

    func_020785a4(&y, &b1, &w, &v14, &b2, &x);

    r6 = func_0207cec0(&data_021e5a2c, y);
    if (r6 == 0) {
        return;
    }

    func_0207f1c8();
    r7 = func_0209b5e8();

    r4 = 0;
    if (b2) {
        temp = 1;
    } else {
        temp = r4;
    }
    if (temp > 0) {
        r5 = 1;
    } else {
        r5 = 0;
    }

    func_0207f270(r6);
    func_020794d0();
    func_0209bd5c();

    if (v14 < 4) {
        if (func_020984fc() != 0) {
            r4 = func_02099870();
        }
    }

    func_0209b9cc(r7, b1, &w, r4, r5);
}
