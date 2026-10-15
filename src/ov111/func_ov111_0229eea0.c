/* func_ov111_0229eea0 @ 0x0229eea0, 0x68 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern __arm void __cxa_vec_cleanup(char *p, int a, int b, void (*f)(void *));
extern void *func_ov002_0220ba0c(char *p);
extern void *func_ov002_02209cb4(char *p);
extern void *func_020a887c(char *p);
extern void *func_0203a3ec(char *p);
extern void *func_ov002_0220826c(char *p);
extern int **func_02070be8(void *unused0);

extern unsigned char data_ov111_022a0ff0[];
extern unsigned char data_ov111_022a1008[];

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

char *func_ov111_0229eea0(char *obj)
{
    *(void **) obj = (void *) data_ov111_022a1008;
    func_ov002_0220ba0c(obj + 0x3d9c);
    func_ov002_02209cb4(obj + 0x3d38);
    *(void **) (obj + 0x3d08) = (void *) data_ov111_022a0ff0;
    func_020a887c(obj + 0x3d08);
    func_0203a3ec(obj + 0x3cd4);
    __cxa_vec_cleanup(obj + 0x23fc, 2, 0x6c, VisitElement_02070be8);
    func_ov002_0220826c(obj);
    return obj;
}

#undef VisitElement_02070be8
