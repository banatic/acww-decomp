/* func_020acb94 @ 0x020acb94, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208af30(void *);
extern void *func_0208ec40(void *, int);
extern void func_0208ea6c(void *, int);
extern int data_020e4014;

void *func_020acb94(void *obj)
{
    func_0208af30(obj);
    *(unsigned int *) obj = (unsigned int) &data_020e4014;
    ((unsigned int *) obj)[3] = 0x800;
    func_0208ec40((char *) obj + 0x10, 1);
    func_0208ea6c((char *) obj + 0x10, 0);
    return obj;
}
