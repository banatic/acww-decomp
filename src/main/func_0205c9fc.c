/* func_0205c9fc @ 0x0205c9fc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int GX_ResetBankForSubOBJExtPltt(void);
extern int data_021c9b14;

void func_0205c9fc(void)
{
    int result;
    result = GX_ResetBankForSubOBJExtPltt();
    data_021c9b14 = result;
}
