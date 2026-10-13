/* func_02070760 @ 0x02070760, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef void *(*Func)(void *, int);
extern Func data_020df6bc[];

void *func_02070760(void *p, int arg)
{
    return data_020df6bc[*(unsigned char *) p](p, arg);
}
