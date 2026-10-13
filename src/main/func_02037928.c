/* func_02037928 @ 0x02037928, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020379ac(void *p);
extern void func_02064328(char *buf, const char *fmt, int a, int b, int c);
extern int func_02064b2c(char *buf, void *p, int a, int b);
extern void *func_021077e8(int c);
extern void func_02056064(void *p, int a);
extern void *func_020561cc(void *p, void *q);
extern void func_020e9898(int c);

extern const char data_020da498[];
extern void *data_021fbe94;
extern void *data_021c9b24;

typedef struct {
    unsigned char pad_00[8];
    unsigned char b : 2;
    unsigned char c : 6;
} G_021ebcc8_t;
extern G_021ebcc8_t data_021ebcc8;

void func_02037928(void *arg)
{
    int a, b, c;
    char buf[32];

    a = func_020379ac(arg);
    b = func_020379ac(arg);
    func_02064328(buf, data_020da498, a, b, data_021ebcc8.c + 97);
    c = func_02064b2c(buf, data_021fbe94, -4, 0);
    *(void **) ((char *) arg + 0x630) = func_021077e8(c);
    func_02056064(*(void **) ((char *) arg + 0x630), 0);
    *(void **) ((char *) arg + 0x630) = func_020561cc(*(void **) ((char *) arg + 0x630), data_021c9b24);
    if (c) {
        func_020e9898(c);
    }
}
