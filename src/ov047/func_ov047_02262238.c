/* func_ov047_02262238 @ 0x02262238, 0x84 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016104(void *p);
extern int func_0201c314(void *a, int b);
extern void func_0209129c(int a);
extern void func_0201ad18(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern int func_020147fc(void *a, int b, int c, int d);
extern int data_020c814c;

extern unsigned char data_021fbee8[];

int func_ov047_02262238(void *self)
{
    int v;
    int size;

    size = func_02016104((char *) self + 0x658);
    v = 0;
    if (size != 0) {
        v = func_0201c314(self, size);
    }
    if (*(int *) ((char *) self + 0x73c) != -1) {
        func_0209129c(*(int *) ((char *) self + 0x73c));
        *(int *) ((char *) self + 0x73c) = -1;
    }
    func_0201ad18((int) ((char *) self + 0x3b0), 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_020147fc((char *) self + 0x618, 0, v, 0);
    return 1;
}
