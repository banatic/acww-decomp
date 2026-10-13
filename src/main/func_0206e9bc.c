/* func_0206e9bc @ 0x0206e9bc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02004148(void *ptr);
extern int data_021cfbcc;
extern int data_021cfbac;

void func_0206e9bc(int param)
{
    func_02004148(&data_021cfbcc);
    if (param != 0) {
        data_021cfbac = 0x190;
    } else {
        data_021cfbac = 0x14;
    }
}
