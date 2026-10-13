/* func_0209132c @ 0x0209132c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02091310(int a, int b);
typedef struct {
    void (*handler)(int);
    int pad_04;
} Handler;
extern Handler data_020e2c20[];

void func_0209132c(int a, int b)
{
    unsigned int idx;
    void (*handler)(int);

    if (b == -1) {
        return;
    }
    idx = func_02091310(a, b);
    if (idx >= 0x66) {
        return;
    }
    handler = data_020e2c20[idx].handler;
    if (handler == 0) {
        return;
    }
    handler(b);
}
