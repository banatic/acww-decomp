/* func_ov003_02215af0 @ 0x02215af0, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_020109fc(void *p, int a, int b, int c);
extern int func_02073908(unsigned int a, unsigned int b);
extern void func_ov003_02215b90(void *a, void *b, void *c);
extern void func_02060428(void *a, void *b);
extern void func_0205eae0(void *a, int b, int c, int d);
extern void func_ov003_02215ba8(void *a, void *b, unsigned char c);

void func_ov003_02215af0(unsigned char *self)
{
    struct Output {
        unsigned char flag;
        unsigned char pad[3];
        unsigned int w[3];
    } out;
    unsigned char *r4;
    unsigned int g;
    unsigned int tmp[3];

    r4 = self + 0x8f0;
    func_020109fc(self, 0x54, 3, 0);

    g = data_020ccf94;
    if (func_02073908(g, *(unsigned int *) (self + 0x800)) == 0) {
        func_ov003_02215b90(r4, out.w, &out.flag);
        if (out.flag == 3) {
            tmp[0] = out.w[0];
            tmp[1] = out.w[1];
            tmp[2] = out.w[2];
            func_02060428(self + 0x5c8, tmp);
        }
    }

    func_0205eae0(self + 0x5a0, 0x17, 3, 0);

    if (func_02073908(g, *(unsigned int *) (self + 0x800)) != 0) {
        func_ov003_02215ba8(r4, self + 0x5d0, (unsigned char) (*(unsigned int *) (self + 0x5cc)));
    }
}
