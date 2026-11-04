/* pockets_screen_26: 6 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229f290 @ 0x0229f290, 0x90 bytes, Thumb
 * func_ov096_0229f200 @ 0x0229f200, 0x90 bytes, Thumb
 * func_ov096_0229f1a8 @ 0x0229f1a8, 0x58 bytes, Thumb
 * func_ov096_0229f150 @ 0x0229f150, 0x58 bytes, Thumb
 * func_ov096_0229f0dc @ 0x0229f0dc, 0x74 bytes, Thumb
 * func_ov096_0229f088 @ 0x0229f088, 0x54 bytes, Thumb
 */

extern int func_ov096_0229f7ac(char *, int);
extern int func_ov096_0229f548(char *, int);
extern int func_ov096_0229f810(char *, int);
extern int func_ov096_0229f800(char *, int);
extern int func_ov094_0229aba4(char *, int);
extern int func_ov094_0229b384(char *, int);
extern int func_ov090_022990b8(int);
extern int func_ov094_0229ab90(int, int);
extern int func_ov094_0229b328(int, int);
extern int func_ov094_0229a8bc(unsigned char *a, int b);
extern int func_ov094_0229b788(unsigned char *a, int b);
extern int func_ov096_0229f830(void *a, void *b);
extern int func_ov096_0229f820(void *a, void *b);
extern int func_ov094_0229a69c(void *a, void *b);
extern int func_ov094_0229b30c(void *a, void *b);
extern int func_ov096_0229f054(void *a, int b);
extern unsigned short func_02065f18(int x);
extern unsigned short func_ov094_0229aaac(void *addr, int x);
extern int func_02065f08(void *argument0);
extern int func_ov094_0229aa84(void *, int);

int func_ov096_0229f290(char *a, int b)
{
    int ret;
    if (func_ov096_0229f830((void *) a, (void *) b) != 0) {
        ret = func_ov096_0229f7ac(a, b);
        return func_ov094_0229aba4(a + 0x358, ret);
    }
    if (func_ov096_0229f820((void *) a, (void *) b) != 0) {
        ret = func_ov096_0229f548(a, b);
        return func_ov094_0229b384(a + 0xdb8, ret);
    }
    if (func_ov096_0229f810(a, b) != 0) {
        b -= 0x19;
        return func_ov090_022990b8(b) - 8;
    }
    if (func_ov096_0229f800(a, b) != 0) {
        ret = func_ov096_0229f7ac(a, b);
        return func_ov094_0229aba4(a + 0x358, ret);
    }
    return 0;
}

int func_ov096_0229f200(int param1, int param2)
{
    if (func_ov096_0229f830((void *) param1, (void *) param2)) {
        return func_ov094_0229ab90(param1 + 0x358, func_ov096_0229f7ac((char *) param1, param2));
    }
    if (func_ov096_0229f820((void *) param1, (void *) param2)) {
        return func_ov094_0229b328(param1 + 0xdb8, func_ov096_0229f548((char *) param1, param2));
    }
    if (func_ov096_0229f810((char *) param1, param2)) {
        return 8;
    }
    if (func_ov096_0229f800((char *) param1, param2)) {
        return func_ov094_0229ab90(param1 + 0x358, func_ov096_0229f7ac((char *) param1, param2));
    }
    if (param2 == 0x21) {
        return 0xb0;
    }
    return 0;
}

int func_ov096_0229f1a8(unsigned char *arg0, int arg1)
{
    if (func_ov096_0229f830((void *) arg0, (void *) arg1) != 0) {
        return func_ov094_0229a8bc(arg0 + 0x358, func_ov096_0229f7ac((char *) arg0, arg1));
    } else if (func_ov096_0229f820((void *) arg0, (void *) arg1) != 0) {
        return func_ov094_0229b788(arg0 + 0xdb8, func_ov096_0229f548((char *) arg0, arg1));
    }
    return 0;
}

int func_ov096_0229f150(void *self, void *arg)
{
    if (func_ov096_0229f830(self, arg)) {
        return func_ov094_0229a69c((char *) self + 0x358, (void *) func_ov096_0229f7ac((char *) self, (int) arg));
    }
    if (func_ov096_0229f820(self, arg)) {
        return func_ov094_0229b30c((char *) self + 0xdb8, (void *) func_ov096_0229f548((char *) self, (int) arg));
    }
    return 1;
}

unsigned short func_ov096_0229f0dc(void *a, int b)
{
    if (func_ov096_0229f830(a, (void *) b)) {
        return func_ov094_0229aaac((char *) a + 0x358, func_ov096_0229f7ac((char *) a, b));
    } else if (func_ov096_0229f820(a, (void *) b)) {
        if (func_ov096_0229f150(a, (void *) b)) {
            return 0xFFF1;
        } else {
            return func_02065f18(func_ov096_0229f054(a, b));
        }
    } else if (func_ov096_0229f800((char *) a, b)) {
        return *(unsigned short *) ((char *) a + 0xae);
    }
    return 0xFFF1;
}

int func_ov096_0229f088(void *a, void *b)
{
    if (func_ov096_0229f830(a, b)) {
        return func_ov094_0229aa84((void *) ((char *) a + 0x358), func_ov096_0229f7ac((char *) a, (int) b));
    } else if (func_ov096_0229f820(a, b)) {

        return func_02065f08((void *) func_ov096_0229f054(a, (int) b));
    } else {
        func_ov096_0229f800((char *) a, (int) b);
        return 0;
    }
}
