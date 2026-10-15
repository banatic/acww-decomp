/* func_ov003_02216644 @ 0x02216644, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02216688(char *, unsigned char, unsigned char, int *);
extern void func_020109a0(char *, int b, int c, unsigned short d);
extern unsigned int *func_0200f27c(char *, int);

typedef struct {
    unsigned char pad_00[0xC];
    unsigned char sub[4];
} QType;

void func_ov003_02216644(char *a, QType *b, int previous)
{
    unsigned char *p = b->sub;
    unsigned char v2 = p[2];
    unsigned char v3 = p[3];
    unsigned char v1 = p[1];
    unsigned char v0 = b->sub[0];
    int local[3];

    local[0] = v0;
    local[1] = v1;
    func_ov003_02216688(a + 0x7d4, v2, v3, local);
    func_020109a0(a, 0x44, 3, 0);
    func_0200f27c(a, 0x1c);
}
