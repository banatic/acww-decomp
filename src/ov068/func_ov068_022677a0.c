/* func_ov068_022677a0 @ 0x022677a0, 0x90 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *, int);
extern int func_02019de8(void *);
extern int gt2GetIncomingBufferSize(void *);
extern int func_0201c314(unsigned char *, int);
extern void func_ov068_02266c34(void *, void *, int, int, int, const void *, int, int, int);
extern void func_020147fc(void *, int, int, int);

extern const int data_021fbee8[];
extern int data_020c814c;

void func_ov068_022677a0(char *self, unsigned char *obj)
{
    int a, b;

    if (func_020164a0(obj + 0x334, 0) == 0xec) {
        if (func_02019de8(obj + 0x564) == 0) {
            return;
        }
    }
    a = gt2GetIncomingBufferSize(obj + 0x680);
    b = 0;
    if (a != 0) {
        b = func_0201c314(obj, a);
    }
    func_ov068_02266c34(obj + 0x898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    func_020147fc(obj + 0x618, 0, b, 0);
    self[0x1c] = 1;
}
