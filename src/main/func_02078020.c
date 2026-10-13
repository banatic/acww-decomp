/* func_02078020 @ 0x02078020, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e1870;
extern void func_020a887c(void *obj);
extern void func_020edb3c(void *obj);

void *func_02078020(void *obj)
{
    *(int **) obj = &data_020e1870;
    func_020a887c(obj);
    func_020edb3c(obj);
    return obj;
}
