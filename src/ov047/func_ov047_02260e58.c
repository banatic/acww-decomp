/* func_ov047_02260e58 @ 0x02260e58, 0x68 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern short *func_0209d358(int, int);
extern int func_0202e9fc(void);
extern int func_02071298(const char *, const char *);
extern void func_02014f60(const char *);

extern unsigned char data_021f38f8[];

void func_ov047_02260e58(char *p)
{
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        func_02014f60(p);
        *(int *) (p + 0xd0) = 0x20;
        return;
    }
    if (func_0202e9fc() != 0 && func_02071298((const char *) data_021f38f8, p + 0xce) == 0) {
        *(int *) (p + 0xd0) = 0x1e;
        return;
    }
    func_02014f60(p);
    *(int *) (p + 0xd0) = 0x20;
}
