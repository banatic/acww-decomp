/* func_02070bc4 @ 0x02070bc4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e179c;
extern void func_02070b84(int **ptr);
extern void func_020a8c38(int **ptr);
extern void func_020edb3c(int **ptr);

int **func_02070bc4(int **ptr)
{
    *ptr = &data_020e179c;
    func_02070b84(ptr);
    func_020a8c38(ptr);
    func_020edb3c(ptr);
    return ptr;
}
