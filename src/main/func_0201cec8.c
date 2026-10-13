/* func_0201cec8 @ 0x0201cec8, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void *func_020160b4(void *p0, char *p1);
void func_0201cf54(void *p0);
void func_020ab670(void *p, unsigned char a, signed char b);
int func_020644cc(int);
void func_020ab628(void *p, int i, char *c, int zero, signed long lit, int zero2, int zero3);
void func_020ab5f8(void *p);

extern unsigned char data_021f43f8[];

void func_0201cec8(void *p0, char *p1)
{
    void *result;
    int zero;
    int i;
    char c;
    unsigned char *p;
    int diff;
    int add;
    unsigned char b;

    result = func_020160b4(p0, p1);
    if (result == 0) {
        return;
    }

    func_0201cf54(p0);
    func_020ab670(result, (unsigned char) p1[0x20], (signed char) p1[0x21]);

    zero = 0;
    for (i = 0; i < (unsigned char) p1[0x20]; i++) {
        p = (unsigned char *) p1 + (i << 1);
        diff = p[1] - ((unsigned char *) p1)[i * 2] + 1;
        add = func_020644cc(diff);
        b = ((unsigned char *) p1)[i * 2];
        c = (char) (b + add);
        func_020ab628(result, i, &c, zero, (unsigned int) data_021f43f8, zero, zero);
        *(unsigned int *) ((char *) p0 + i * 4 + 0x140) = *(unsigned int *) ((char *) p1 + i * 4 + 0xc);
    }

    func_020ab5f8(result);
}
