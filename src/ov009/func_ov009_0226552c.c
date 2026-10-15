/* func_ov009_0226552c @ 0x0226552c, 0x6c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203f130(void *p);
extern void *func_02066a30(void *p);
extern void *func_02055210(void *p);
extern void *func_020b33e0(void *p);
extern void *func_ov009_02262f8c(void *p);
extern void func_0209d34c(void *p);
extern char data_ov009_022658dc;
extern char data_ov009_022659a0;

void *func_ov009_0226552c(void *obj)
{
    func_0203f130(obj);
    func_02066a30((char *) obj + 0xec);
    *(void **) obj = (void *) &data_ov009_022658dc;
    *(void **) ((char *) obj + 0xec) = (void *) &data_ov009_022659a0;
    *(unsigned short *) ((char *) obj + 0x136) = 0xfff1;
    func_02055210((char *) obj + 0x13c);
    func_020b33e0((char *) obj + 0x1f4);
    func_ov009_02262f8c((char *) obj + 0x238);
    func_0209d34c((char *) obj + 0x292);
    return obj;
}
