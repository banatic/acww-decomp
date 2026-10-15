/* func_020b5524 @ 0x020b5524, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *obj);
extern void func_020a8c1c(void *obj);
extern int data_020e51b8;

void *func_020b5524(void *obj)
{
    func_020a8cac(obj);
    *(void **) obj = (void *) &data_020e51b8;
    ((char *) obj)[0x1c] = 0;
    func_020a8c1c(obj);
    return obj;
}
