/* func_ov091_02299494 @ 0x02299494, 0x48 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *p);
extern void *func_0206e388(void *p);
extern void *func_ov002_0220b428(void *p);
extern void *func_ov002_02209c78(void *p);
extern int data_ov091_02299530;

void *func_ov091_02299494(void)
{
    void *p;
    p = func_ov002_02207f80(0x498);
    if (p == 0) {
        goto end;
    }
    func_ov002_0220830c(p);
    *(int *) p = (int) &data_ov091_02299530;
    func_0206e388((char *) p + 0x94);
    func_ov002_0220b428((char *) p + 0x3bc);
    func_ov002_02209c78((char *) p + 0x434);
end:
    return p;
}
