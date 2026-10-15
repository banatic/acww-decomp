/* func_ov009_022654c0 @ 0x022654c0, 0x6c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov009_022658dc;
extern char data_ov009_022659a0;

extern void *func_0203f130(void *p);
extern void *func_02066a30(void *p);
extern void *func_02055210(void *p);
extern void *func_020b33e0(void *p);
extern void *func_ov009_02262f8c(void *p);
extern void func_0209d34c(void *p);

void *func_ov009_022654c0(void *p)
{
    func_0203f130(p);
    func_02066a30((void *) ((unsigned int) p + 0xEC));
    *(void **) ((unsigned int) p) = &data_ov009_022658dc;
    *(void **) ((unsigned int) p + 0xEC) = &data_ov009_022659a0;
    *(unsigned short *) ((unsigned int) p + 0x136) = 0xFFF1;
    func_02055210((void *) ((unsigned int) p + 0x13C));
    func_020b33e0((void *) ((unsigned int) p + 0x1F4));
    func_ov009_02262f8c((void *) ((unsigned int) p + 0x238));
    func_0209d34c((void *) ((unsigned int) p + 0x292));
    return p;
}
