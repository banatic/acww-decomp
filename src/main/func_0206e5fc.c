/* func_0206e5fc @ 0x0206e5fc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02050e68(void);
extern void func_02011eec(void);
extern void func_020ba340(void);
extern void func_0205c080(void);
extern void func_02004b30(int);

void func_0206e5fc(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    func_02050e68();
    func_02011eec();
    func_020ba340();
    func_0205c080();
    if (r4 == 0) {
        result = 0;
    } else {
        result = 1;
    }
    func_02004b30(result);
}
