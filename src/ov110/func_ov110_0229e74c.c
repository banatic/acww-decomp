/* func_ov110_0229e74c @ 0x0229e74c, 0x60 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f58c(void *);
extern int func_ov110_0229e7ac(void *);
extern void func_ov110_0229cbe0(void *);
extern void func_ov002_02207d24(void *, int);
extern void func_ov110_0229c3b8(void *, int);
extern void func_ov110_0229e370(void *);
extern void func_ov110_0229e7cc(void *);
extern void func_ov110_0229e368(void *);

int func_ov110_0229e74c(void *obj)
{
    func_0206f58c(obj);
    if (func_ov110_0229e7ac(obj) != 0 &&
        (((unsigned char *) obj)[0x8d] == 0 || ((unsigned char *) obj)[0x8d] == 1 || ((unsigned char *) obj)[0x8d] == 4)) {
        func_ov110_0229cbe0(obj);
        func_ov002_02207d24((char *) obj + 0x21f8, 0);
        func_ov110_0229c3b8(obj, 0);
        return 1;
    } else {
        func_ov110_0229e370(obj);
        func_ov110_0229e7cc(obj);
        func_ov110_0229e368(obj);
        return 1;
    }
}
