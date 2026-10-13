/* func_02076d68 @ 0x02076d68, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern unsigned char data_020e54a8;
extern void func_020736bc(int, unsigned char *, int);
extern void func_ov003_0222e6c4(int, int);
extern void func_ov003_0222e7f8(int);

void func_02076d68(int param)
{
    unsigned char local;
    int flag;

    func_020736bc(data_020ccf94, &local, param);
    flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        if (local < 4) {
            func_ov003_0222e6c4(local, 0);
        } else {
            func_ov003_0222e7f8(local);
        }
    }
}
