/* func_0207716c @ 0x0207716c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020736bc(int, int *, int);
extern void func_020348fc(int *);

void func_0207716c(int param, int sequence, unsigned char category, unsigned int player)
{
    int local;
    func_020736bc(data_020ccf94, &local, param);
    func_020348fc(&local);
}
