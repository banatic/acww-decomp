/* func_02039e44 @ 0x02039e44, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c1c(void *);
extern void func_02051ad8(void *);
extern void func_020399c8(void *);
extern void func_0203990c(void *);
extern void func_02039e34(void *);

void func_02039e44(void *p)
{
    func_020a8c1c((char *) p + 0x54);
    func_02051ad8((char *) p + 0x88);
    func_020399c8(p);
    func_0203990c(p);
    ((int *) ((char *) p + 0xa8))[0] = 0;
    ((int *) ((char *) p + 0xac))[0] = 0;
    ((int *) ((char *) p + 0xb0))[0] = 0;
    func_02039e34(p);
}
