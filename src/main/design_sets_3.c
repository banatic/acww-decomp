/* design_sets_3: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02072be0 @ 0x02072be0, 0x6e bytes, Thumb
 * func_02072bd0 @ 0x02072bd0, 0x10 bytes, Thumb
 * func_02072bb0 @ 0x02072bb0, 0x20 bytes, Thumb
 * func_02072ba4 @ 0x02072ba4, 0xc bytes, Thumb
 * func_02072ba0 @ 0x02072ba0, 0x2 bytes, Thumb
 * func_02072b9c @ 0x02072b9c, 0x2 bytes, Thumb
 * func_02072b8c @ 0x02072b8c, 0x10 bytes, Thumb
 * func_02072b74 @ 0x02072b74, 0x16 bytes, Thumb
 * func_02072b64 @ 0x02072b64, 0xe bytes, Thumb
 * func_02072b38 @ 0x02072b38, 0x2c bytes, Thumb
 * func_02072b18 @ 0x02072b18, 0x20 bytes, Thumb
 */

extern int func_02072d4c(int a);
extern void *func_02072ee8(void *record);
extern unsigned char *func_02095040(int a);
extern int func_0209518c(int a, int b);
extern void func_02095038(int a, unsigned char *b);
extern int memcmp(const void *a, const void *b, unsigned int n);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_02072dbc(void *);
extern void *func_02072da4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

int func_02072bd0(int a, int b);
unsigned char func_02072b64(unsigned char *r0, int r1);

void func_02072be0(void *local0, int param1, unsigned char *param2)
{
    unsigned char i;
    int t;
    unsigned char *p;
    int local1;

    for (i = 0; i < 8; i++) {
        t = func_02072d4c(func_02072bd0((int) local0, i));
        local1 = (int) func_02072ee8((void *) t);
        p = func_02095040(local1);
        if (*(unsigned short *) p == *(unsigned short *) param2) {
            if (memcmp(p + 2, param2 + 2, 12) == 0) {
                if (func_0209518c(local1, param1) != 0) {
                    t = (int) func_02072ee8((void *) t);
                    func_02095038(t, func_02095040(param1));
                }
            }
        }
    }
}

int func_02072bd0(int a, int b)
{
    return a + (b & 7) * 0x234;
}

int func_02072bb0(int r0, int index)
{
    int r4 = r0;
    int r0_2 = (int) func_02072b64((unsigned char *) (r4 + 0x11a0), index);
    return r4 + r0_2 * 0x234;
}

int func_02072ba4(int r0)
{
    return r0 + 0x11a0;
}

void func_02072ba0(void *object) {}

void func_02072b9c(void *object) {}

void func_02072b8c(unsigned char *r0)
{
    unsigned char i;
    i = 0;
    do {
        r0[i] = i;
        i = (unsigned char) (i + 1);
    } while (i < 8);
}

void func_02072b74(unsigned char *data, int a, int b)
{
    unsigned char tmp;
    tmp = data[a & 7];
    data[a & 7] = data[b & 7];
    data[b & 7] = tmp;
}

unsigned char func_02072b64(unsigned char *r0, int r1)
{
    unsigned char r0_val;
    int r2;

    r2 = 7;
    r1 &= r2;
    r0_val = r0[r1];
    r0_val &= r2;
    return r0_val;
}

void *func_02072b38(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 8, 0x234, (((void (*)(void *)) func_02072dbc)), (((void (*)(void *)) func_02072da4)));
    return arg;
}

void *func_02072b18(void *ptr)
{
    __cxa_vec_cleanup((void *) (ptr), 8, 0x234, (((void (*)(void *)) func_02072da4)));
    return ptr;
}
