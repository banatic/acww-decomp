/* func_020641b0 @ 0x020641b0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *);
extern int data_020de694;

void *func_020641b0(void *obj)
{
    *(int **) obj = &data_020de694;
    func_020a8c38(obj);
    return obj;
}
