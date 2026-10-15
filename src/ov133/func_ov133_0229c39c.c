/* func_ov133_0229c39c @ 0x0229c39c, 0x38 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208090(void *, int);
extern int func_ov002_0220ab38(void *, int);
extern void func_ov133_0229c050(void *);
extern void func_ov133_0229c0a4(void *);
extern void func_ov133_0229c0f8(void);
extern void func_ov133_0229c340(void *);

void func_ov133_0229c39c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov133_0229c0f8();
    func_ov133_0229c0a4(self);
    func_ov133_0229c050(self);
    func_ov002_02208090(self, 0x1);
    func_ov002_0220ab38(self + 0x180, 0x65);
    func_ov133_0229c340(self);
}
