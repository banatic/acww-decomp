/* func_02019794 @ 0x02019794, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201b188(void *, void *);
extern int func_0201aff8(void *, void *, int);
extern int func_0201afc0(void *);
extern void *func_02019de4(int);
extern void func_02019af0(int, int);
extern int func_02019d0c(int, int, int, int, int, int, int, int, int, unsigned short, int);
extern unsigned short data_020c80f8;

void func_02019794(int p0, void *p1)
{
    func_0201b188((char *) p1 + 0x350, p1);
    if (func_0201aff8((char *) p1 + 0x350, p1, 0) != 0) {
        if (func_0201afc0((char *) p1 + 0x350) != 0) {
            void *p = func_02019de4(p0);
            func_02019d0c(p0, 1, 1, ((int *) p)[1], ((int *) p)[2], 0, 0, 0, 0, data_020c80f8, 0);
        } else {
            func_02019af0(p0, 1);
        }
    }
}
