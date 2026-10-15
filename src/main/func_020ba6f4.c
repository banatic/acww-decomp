/* func_020ba6f4 @ 0x020ba6f4, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern unsigned char data_020d22b8[];
extern char data_020e7aa8[];
extern char data_020e7abc[];
extern char data_021f7280[];
extern int func_02002c6c(void *, void *, unsigned char, int, int, int);
extern void *func_020e9958(void *, int);
extern int func_02064af4(void *, void *, int);
extern void func_020b0f54(void *);
extern int func_02002b40(void *, unsigned char, int, int);
extern void func_020e993c(void *, void *);
extern void func_020b177c(void *, unsigned char);

int func_020ba6f4(int idx)
{
    void *gptr;
    unsigned char byte;
    void *buf;

    gptr = data_021fbe94;
    byte = data_020d22b8[idx];

    if (func_02002c6c(data_020e7aa8, gptr, byte, 0x10, 0x10, 0x1f) == 0) {
        return 0;
    }

    buf = func_020e9958(gptr, 0x1000);
    if (buf == 0) {
        return 0;
    }

    func_02064af4(data_020e7abc, buf, 0x1000);
    func_020b0f54(buf);

    if (func_02002b40(buf, byte, 0x1000, 0) == 0) {
        func_020e993c(gptr, buf);
        return 0;
    } else {
        func_020e993c(gptr, buf);
        func_020b177c(data_021f7280, byte);
        return 1;
    }
}
