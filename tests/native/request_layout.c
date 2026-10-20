/* Request builders whose matching source keeps the header and the payload in separate locals
 * (their ROM bodies pass them 12 bytes apart). Each payload writer marks its payload;
 * func_0200e894, the submission, must find the mark 12 bytes after the header it gets. */
static int failed, submitted;
static unsigned mark;

unsigned int func_0200e92c(void *p)
{
    unsigned *words = p;
    words[0] = words[1] = words[2] = 0;
    return 0;
}
void func_0200e90c(void *p, int a, int b, int c)
{
    int *words = p;
    words[0] = a;
    words[1] = b;
    words[2] = c;
}
int func_0200e894(void *self, void *p)
{
    (void) self;
    if (((unsigned *) p)[3] != mark) {
        failed++;
    }
    submitted++;
    return 7;
}
int func_0200e91c(void *p)
{
    (void) p;
    return 0;
}
/* other callees: nothing to do */
int data_ov004_02247780;
void func_0200fa1c(int *out, void *a, void *b, void *c, void *d)
{
    (void) a;
    (void) b;
    (void) c;
    (void) d;
    out[0] = out[1] = out[2] = 0;
}
void func_0200f268(void *p, int n)
{
    (void) p;
    (void) n;
}
void func_0204f7e0(int *out, void *p)
{
    (void) p;
    out[0] = out[1] = out[2] = 0;
}

#define WRITER(name)                                                                                                          \
    void name(unsigned *payload)                                                                                              \
    {                                                                                                                         \
        payload[0] = mark;                                                                                                    \
    }
WRITER(func_02009a9c)
WRITER(func_0200a6f0)
WRITER(func_0200ad78)
WRITER(func_0200b894)
WRITER(func_0200c3f0)
WRITER(func_0200cc40)
WRITER(func_0200dc00)
WRITER(func_ov003_0220fb80)
WRITER(func_ov003_0220fdf4)
WRITER(func_ov003_02212878)
WRITER(func_ov003_02212d04)
WRITER(func_ov003_02215664)
WRITER(func_ov003_02216460)
WRITER(func_ov003_022166e8)
WRITER(func_ov003_02216b08)
WRITER(func_ov003_022172bc)
WRITER(func_ov003_02217894)
WRITER(func_ov003_0221871c)
WRITER(func_ov003_02218918)
WRITER(func_ov004_02228678)
WRITER(func_ov004_0222ac74)
WRITER(func_0200a4ac)
WRITER(func_0200be0c)
WRITER(func_0200c94c)
WRITER(func_0200d1e0)
WRITER(func_0200d528)
WRITER(func_ov003_0220f7b8)
WRITER(func_ov003_02210114)
WRITER(func_ov003_022122fc)
WRITER(func_ov003_02218f0c)
WRITER(func_ov003_02218fec)
WRITER(func_ov004_02228164)
WRITER(func_ov004_02229078)
WRITER(func_ov004_022292c0)
WRITER(func_ov004_02229508)
WRITER(func_ov004_022297c4)
WRITER(func_ov004_0222a4dc)
WRITER(func_ov004_0222afbc)

/* Called with more arguments than any of them takes (the caller removes them): every pointer
 * points at zeroed memory, every number is 0. */
typedef int Builder(void *, void *, void *, void *, void *, void *, void *, void *);
extern Builder func_02009a44, func_0200a6a0, func_0200acd4, func_0200ad24, func_0200b7e8, func_0200c3b0, func_0200cc00,
    func_0200dbb4, func_ov003_0220fb30, func_ov003_0220fda0, func_ov003_02212830, func_ov003_02212c10, func_ov003_02215624,
    func_ov003_02216410, func_ov003_02216698, func_ov003_02216ab8, func_ov003_022171ec, func_ov003_02217838,
    func_ov003_022186cc, func_ov003_022188d0, func_ov004_02228628, func_ov004_0222ac24, func_0200a448, func_0200b83c,
    func_0200bdbc, func_0200c904, func_0200d1a0, func_0200d4e8, func_ov003_0220f768, func_ov003_022100c4, func_ov003_022122ac,
    func_ov003_02218ec4, func_ov003_02218fac, func_ov004_02228100, func_ov004_02229010, func_ov004_02229258,
    func_ov004_022294a0, func_ov004_02229774, func_ov004_0222a494, func_ov004_0222af6c;
static Builder *const builders[] = {
    func_02009a44,       func_0200a6a0,       func_0200acd4,       func_0200ad24,       func_0200b7e8,
    func_0200c3b0,       func_0200cc00,       func_0200dbb4,       func_ov003_0220fb30, func_ov003_0220fda0,
    func_ov003_02212830, func_ov003_02212c10, func_ov003_02215624, func_ov003_02216410, func_ov003_02216698,
    func_ov003_02216ab8, func_ov003_022171ec, func_ov003_02217838, func_ov003_022186cc, func_ov003_022188d0,
    func_ov004_02228628, func_ov004_0222ac24, func_0200a448,       func_0200b83c,       func_0200bdbc,
    func_0200c904,       func_0200d1a0,       func_0200d4e8,       func_ov003_0220f768, func_ov003_022100c4,
    func_ov003_022122ac, func_ov003_02218ec4, func_ov003_02218fac, func_ov004_02228100, func_ov004_02229010,
    func_ov004_02229258, func_ov004_022294a0, func_ov004_02229774, func_ov004_0222a494, func_ov004_0222af6c,
};

int main(void)
{
    static unsigned zero[0x1000];
    for (unsigned i = 0; i < sizeof(builders) / sizeof(builders[0]); i++) {
        mark = 0x5a000000u + i;
        int before = submitted;
        builders[i](zero, zero, zero, zero, 0, 0, 0, 0);
        if (submitted != before + 1) {
            return 20 + (int) i;
        }
    }
    return failed;
}
