/* func_020784b0 @ 0x020784b0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020784b0(unsigned int param1, unsigned int param2)
{
    extern unsigned int data_020ccf94;
    extern int func_02073d90(unsigned int);
    extern void func_02078460(unsigned int *, unsigned int, unsigned int);
    extern void func_02073820(unsigned int);
    extern void func_020737f0(unsigned int, unsigned int *, int);
    extern void func_02073770(unsigned int, int, int);

    unsigned int local;
    unsigned int *ptr;

    if (func_02073d90(data_020ccf94)) {
        func_02078460(&local, param1, param2);
        ptr = (unsigned int *) data_020ccf94;
        func_02073820((unsigned int) ptr);
        func_020737f0((unsigned int) ptr, &local, 3);
        func_02073770((unsigned int) ptr, 0x3f, 4);
    }
}
