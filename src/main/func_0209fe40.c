/* func_0209fe40 @ 0x0209fe40, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020e3808;
extern void *data_020e3804;
extern int data_020e3800;

extern int func_0209f150(void *ptr, int size);
extern unsigned char *strcpy(void *dst, const void *src);
extern char *func_0212d914(void *dst, const void *src);
extern void func_02073100(void);
extern int func_020eb108(void *dst, const void *src, int size, int arg);

extern unsigned char data_021dc7a8[];
extern unsigned char data_021f3cbc[];

int func_0209fe40(void)
{
    char buf[0x80];
    int val;

    if (func_0209f150((void *) data_021dc7a8, 0x14) == 0) {
        goto body;
    } else {
        return 0;
    }

body:
    strcpy(buf, data_020e3808);
    func_0212d914(buf, data_020e3804);
    val = data_020e3800;
    func_02073100();
    if (func_020eb108(buf, (void *) data_021f3cbc, 0xd2, val) != 0) {
        return 1;
    } else {
        return 0;
    }
}
