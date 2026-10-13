/* func_020ba9d8 @ 0x020ba9d8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fea4(int arg);
extern void func_020b1800(void *arg);
extern void func_020bc388(void *arg);
extern void func_020bc380(void *arg);
extern void func_020bb6d8(void *arg);
extern void func_020bbe94(void *arg);
extern int data_021f6cd8;
extern char data_021f7280;
extern char data_021f8b48;
extern char data_021f75b0;

int func_020ba9d8(void *p)
{
    if (data_021f6cd8) {
        if (func_0206fea4(data_021f6cd8) == 0) {
            func_020b1800(&data_021f7280);
        }
        func_020bc388(&data_021f8b48);
    } else {
        func_020bc380(&data_021f8b48);
    }

    func_020bb6d8(&data_021f75b0);
    p = (void *) ((char *) p + 0x50);
    func_020bbe94(p);
    return 1;
}
