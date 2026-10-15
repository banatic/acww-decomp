/* func_ov049_02260420 @ 0x02260420, 0x34 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02072da4(void *);
extern void *func_ov049_022620d0(void *);
extern void *func_0202ee5c(void *);
extern unsigned int data_ov049_02263544;

void *func_ov049_02260420(void *obj)
{
    *(unsigned int *) obj = (unsigned int) &data_ov049_02263544;
    func_02072da4((char *) obj + 0x73c);
    func_ov049_022620d0((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
