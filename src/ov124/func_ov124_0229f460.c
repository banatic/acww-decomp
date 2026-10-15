/* func_ov124_0229f460 @ 0x0229f460, 0x30 bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *self, int a, int b, void *fp1, void *fp2);
extern void *func_ov002_0220b3c4(void *ptr);

extern int **func_02070be8(void *unused0);
extern void *func_02070c08(void *unused0);

#define VisitElement_02070c08 (void *) func_02070c08
#define VisitElement_02070be8 (void *) func_02070be8

void *func_ov124_0229f460(void *self)
{
    __cxa_vec_ctor(self, 1, 0x6c, VisitElement_02070c08, VisitElement_02070be8);
    func_ov002_0220b3c4((char *) self + 0x6c);
    return self;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8
