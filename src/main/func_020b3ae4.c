/* func_020b3ae4 @ 0x020b3ae4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e50e8;
extern void func_02031e84(void *a);

void *func_020b3ae4(void *obj)
{
    void *p;

    p = (void *) &data_020e50e8;
    *(void **) obj = p;
    func_02031e84(obj);
    return obj;
}
