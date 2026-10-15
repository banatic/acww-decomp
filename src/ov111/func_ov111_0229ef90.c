/* func_ov111_0229ef90 @ 0x0229ef90, 0x20 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a887c(void *);
extern void func_020edb3c(void *);
extern unsigned int data_ov111_022a0ff0;

void *func_ov111_0229ef90(void *obj)
{
    void *p = obj;
    *(unsigned int *) p = (unsigned int) &data_ov111_022a0ff0;
    func_020a887c(obj);
    func_020edb3c(p);
    return p;
}
