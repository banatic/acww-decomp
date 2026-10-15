/* func_02054354 @ 0x02054354, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020548cc(void *, int);
extern int func_02056548(int, void *, int);
extern int data_020dd030;

int func_02054354(int *obj, int arg)
{
    int val;
    int *p;

    if (!func_020548cc(obj, arg)) {
        return 0;
    }
    val = func_02056548(*(int *) ((char *) obj + 0x5c), &data_020dd030, arg);
    p = (int *) ((char *) obj + 0x154);
    *p = val;
    return *p != 0;
}
