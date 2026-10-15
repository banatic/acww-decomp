/* func_02009c08 @ 0x02009c08, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_020984fc(int);
extern int func_02099728(unsigned int);
extern void func_0200f1a4(int, int, unsigned short);

void func_02009c08(int arg0)
{
    int val;
    int val2;
    unsigned short val3;

    val = data_020ccf94;
    val2 = *(int *) (arg0 + 0x800);
    if (func_02073908(val, val2) != 0) {
        val = *(int *) (arg0 + 0x800);
        val2 = func_02099728((unsigned int) func_020984fc(val));
        if (val2 != 0) {
            val3 = *(unsigned short *) val2;
            func_0200f1a4(arg0, 3, val3);
        }
    }
}
