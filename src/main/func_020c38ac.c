/* func_020c38ac @ 0x020c38ac, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern unsigned int *func_0202eb88(void *object);
extern int data_020c8120;

int func_020c38ac(void *param1)
{
    int result;

    if (func_020b65c4() != 0) {

        result = (int) func_0202eb88(param1);
    } else {
        result = data_020c8120;
    }
    return result;
}
