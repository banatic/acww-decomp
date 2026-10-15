/* func_ov068_02268d54 @ 0x02268d54, 0x88 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int gt2GetIncomingBufferSize(void *);
extern int func_0201c314(unsigned char *, int);
extern void func_02013c0c(void *);
extern void func_ov068_02266c34(void *, void *, int, int, int, const void *, int, int, int);
extern int func_020147fc(void *, int, int, int);
extern void func_0201cbbc(void *);

extern const int data_021fbee8[];
extern int data_020c814c;

int func_ov068_02268d54(char *self, unsigned char *obj)
{
    int a, b;

    a = gt2GetIncomingBufferSize(obj + 0x680);
    b = 0;
    if (a != 0) {
        b = func_0201c314(obj, a);
    }
    func_02013c0c(obj + 0x558);
    func_ov068_02266c34(obj + 0x898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    func_020147fc(obj + 0x618, 0, b, 1);
    func_0201cbbc(obj + 0x83c);
    self[0x1c] = 0;
    return 1;
}
