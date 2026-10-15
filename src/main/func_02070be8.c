/* func_02070be8 @ 0x02070be8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e179c;
extern void func_02070b84(int **param);
extern void *func_020a8c38(int **param);

int **func_02070be8(int **param)
{
    *param = &data_020e179c;
    func_02070b84(param);
    func_020a8c38(param);
    return param;
}
