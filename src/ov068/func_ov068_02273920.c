/* func_ov068_02273920 @ 0x02273920, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov068_02277e50;
extern void func_ov068_022746fc(void *);
extern void func_0202ee5c(void *);

void *func_ov068_02273920(void *arg0)
{
    *((void **) arg0) = (void *) &data_ov068_02277e50;
    func_ov068_022746fc((char *) arg0 + 0x65c);
    func_0202ee5c(arg0);
    return arg0;
}
