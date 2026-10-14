/* func_02083744 @ 0x02083744, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e1ae4;
extern void __cxa_vec_cleanup(void *, int, int, void (*)());
extern void func_02083c78(void *);
extern void func_020837d0(void);

void *func_02083744(void *param)
{
    void *p;
    p = param;
    *(int **) p = &data_020e1ae4;
    __cxa_vec_cleanup((char *) p + 8, 5, 2, func_020837d0);
    func_02083c78(p);
    return p;
}
