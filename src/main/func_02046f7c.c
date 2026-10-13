/* func_02046f7c @ 0x02046f7c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern void func_02046fa4(int);
extern void func_02047050(int);

void func_02046f7c(int arg)
{
    if (func_02073d90(data_020ccf94) != 0) {
        func_02046fa4(arg);
    } else {
        func_02047050(arg);
    }
}
