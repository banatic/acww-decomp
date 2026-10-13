/* func_020477e4 @ 0x020477e4, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df7c(unsigned int *);
extern void *func_0204cc04(int);
extern int func_0209dee8(void);
extern int func_02047854(int, unsigned short, int, int, int);
extern void func_0204cbc0(int, unsigned short);

typedef struct {
    unsigned short a;
    unsigned char b;
    unsigned char pad_03;
    unsigned int c;
    unsigned int d;
} Entry;

void func_020477e4(int p1, int p2, int p3, int p4, int p5)
{
    Entry *p;
    unsigned int q;
    int i;
    unsigned short a;
    unsigned char b;

    func_0209df7c(&q);
    p = (Entry *) func_0204cc04(0);

    for (i = 0; i < 4; p++, i++) {
        a = p->a;
        if (a == 99) {
            continue;
        }
        b = p->b;
        if (b != func_0209dee8() || p->c > q || p->d < q) {
            if (func_02047854(p1, a, p2, p3, p4) != 0) {
                func_0204cbc0(p5 + 0x17254, a);
            }
        }
    }
}
