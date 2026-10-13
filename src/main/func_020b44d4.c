/* func_020b44d4 @ 0x020b44d4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d2084[];
extern unsigned char data_020e52f4[];
extern void func_020b49d4(void *a, unsigned char *b, unsigned char *c);
extern void func_020b4a20(void *a, unsigned char *b, unsigned char *c);

void func_020b44d4(void *a, int idx, int cond)
{
    unsigned char ch;
    unsigned char *dst;
    ch = data_020d2084[idx];
    dst = data_020e52f4;
    if (cond != 0) {
        func_020b49d4(a, &ch, dst);
    } else {
        func_020b4a20(a, &ch, dst);
    }
}
