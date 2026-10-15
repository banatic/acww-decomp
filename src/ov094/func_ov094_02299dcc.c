/* func_ov094_02299dcc @ 0x02299dcc, 0x50 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064328(void *dst, const void *src, int len);
extern int func_02064af4(void *dst, const void *src, int len);
extern void func_ov094_022999a8(void *self, int arg);

extern const char data_ov094_0229be20[];
extern const char data_ov094_0229be3c[];

void func_ov094_02299dcc(void *self, const void *src, int flag)
{
    char local[0x2c];
    void *dst;

    if (flag == 0) {
        func_02064328(local, data_ov094_0229be20, (int) src);
    } else {
        func_02064328(local, data_ov094_0229be3c, (int) src);
    }

    dst = (char *) self + 0x9b8;
    func_02064af4(local, dst, 0xc80);

    *(unsigned char *) ((char *) self + 0x14) = (unsigned char) (unsigned int) src;

    func_ov094_022999a8(self, 4);
}
