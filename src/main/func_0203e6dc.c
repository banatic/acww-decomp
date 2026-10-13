/* func_0203e6dc @ 0x0203e6dc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095d84(void);
extern int func_02095904(void);

int func_0203e6dc(void *arg0)
{
    int val;
    int val2;

    val = func_02095d84();
    if (val == 0) {
        return 0;
    }
    val2 = func_02095904();
    if (val2 == 0) {
        return 0;
    }
    *(unsigned char *) ((int) arg0 + 0x16) = 5;
    return 1;
}
