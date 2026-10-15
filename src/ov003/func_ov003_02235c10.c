/* func_ov003_02235c10 @ 0x02235c10, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void *func_ov003_0222d520(void *unused0);
extern void *data_ov003_022617bc;

#define VisitElement_ov003_0222d520 (void *) func_ov003_0222d520

void func_ov003_02235c10(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(&data_ov003_022617bc, 0x8, 0x25c, VisitElement_ov003_0222d520);
}

#undef VisitElement_ov003_0222d520
