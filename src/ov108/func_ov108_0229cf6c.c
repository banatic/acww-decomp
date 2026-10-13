/* func_ov108_0229cf6c @ 0x0229cf6c, 0x3c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov108_0229c810(void *);
extern void func_ov108_0229c9d8(void *);
extern void func_ov108_0229caec(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov108_0229cf6c(void *p)
{
    ((unsigned char *) p)[0x2ae] = 0x16;
    func_ov108_0229c810(p);
    func_ov002_02207fc0(p);
    func_ov108_0229c9d8(p);
    func_ov002_02208098(p, 6);
    func_ov108_0229caec(p, ((unsigned char *) p)[0x2b0]);
}
