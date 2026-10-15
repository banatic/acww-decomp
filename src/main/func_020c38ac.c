/* func_020c38ac @ 0x020c38ac, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_0202eb88(void);
extern int data_020c8120;

int func_020c38ac(int param1)
{
    int result;
    int temp;

    if (func_020b65c4() != 0) {
        asm { add r0, param1, #0 }
        result = func_0202eb88();
    } else {
        result = data_020c8120;
    }
    return result;
}
