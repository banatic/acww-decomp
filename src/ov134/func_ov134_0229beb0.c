/* func_ov134_0229beb0 @ 0x0229beb0, 0x24 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_ov002_0220a5e4(void *);
extern int **func_02070be8(void *unused0);

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

char *func_ov134_0229beb0(char *obj)
{
    __cxa_vec_cleanup(obj + 0xd8, 0x11, 0x6c, VisitElement_02070be8);
    func_ov002_0220a5e4(obj + 0x18);
    return obj;
}

#undef VisitElement_02070be8
