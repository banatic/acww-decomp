/* func_02094e04 @ 0x02094e04, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094ef4(void);

void func_02094e04(void *arg0, int arg1)
{
    func_02094ef4();
    *(int *) ((char *) arg0 + 0x54) = arg1;
}
