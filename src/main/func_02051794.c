/* func_02051794 @ 0x02051794, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206493c(const void *a, int b, unsigned int c, ...);
extern int func_0212a13c(void *dst, const void *src, int param);
extern int FS_OpenFile(int *dst, const void *src);

extern const unsigned char data_020dcfa8[];
extern const unsigned char data_020dcfbc[];
extern const unsigned char data_020dcfcc[];
extern unsigned int data_020cb918[2];

void func_02051794(int *out, int p1, int p2, int p3, unsigned char byte_param)
{
    int local[2];
    unsigned char buffer[0x84];
    int i;

    for (i = 0; i < 2; i++) {
        int result;
        if (p2 != 0) {
            result = func_0206493c(data_020dcfa8, p1, data_020cb918[i], p2);
        } else {
            result = func_0206493c(data_020dcfbc, p1, data_020cb918[i]);
        }
        local[i] = result;
    }

    out[0] = local[0];
    out[1] = local[1];

    func_0212a13c(buffer, data_020dcfcc, p1);
    FS_OpenFile(out + 5, buffer);

    out[3] = p3;
    ((unsigned char *) out)[0x10] = byte_param;
}
