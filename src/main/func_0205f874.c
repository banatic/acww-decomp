/* func_0205f874 @ 0x0205f874, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f8b4(void);
extern int func_0205f974(int);
extern int func_0205f970(void);
extern int func_02064af4(int, int, int);

int func_0205f874(int param1, int param2)
{
    int val;
    int val2;
    int val3;
    int val4;

    val = func_0205f8b4();
    val2 = func_0205f974(param2);
    val3 = func_0205f970();
    val4 = func_02064af4(val2, val, val3);
    return val4;
}
