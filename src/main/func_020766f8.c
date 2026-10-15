/* func_020766f8 @ 0x020766f8, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int data_021e5a2c;

void func_020736bc(void *a, int *b, int c);
void func_020785a4(int *p0, unsigned char *p1, unsigned short *p2, int *p3, unsigned char *p4, int *p5);
int func_0207cec0(int *p, int v);
unsigned int func_0207f1c8(unsigned int object);
int func_0209b5e8(int);
int func_0207f270(int v);
int func_020794d0(int);
void func_0209bd5c(void *);
int func_020984fc(void *selector);
extern int func_02099870(int);
void func_0209b9cc(int a, unsigned char b, unsigned short *c, int d, int e);

void func_020766f8(int length, int sequence, unsigned char category, unsigned int player)
{
    int tested_value0;
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

    r7 = func_0209b5e8((int) func_0207f1c8((unsigned int) r6));

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

    func_0209bd5c((void *) func_020794d0((int) func_0207f270(r6)));

    if (v14 < 4) {
        if ((tested_value0 = (int) (func_020984fc((void *) v14))) != 0) {
            r4 = func_02099870(tested_value0);
        }
    }

    func_0209b9cc(r7, b1, &w, r4, r5);
}
