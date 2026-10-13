/* func_02035404 @ 0x02035404, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c526c;
extern void func_020374ac(void *p);
extern void func_020364ec(void *p);
extern void func_0203743c(void *p);
extern void func_02036980(void *p);
extern void func_02036830(void *p);
extern void func_02035fc0(void *p);
extern void func_02035dc8(void *p);
extern void func_02035a6c(void *p);

typedef struct {
    char data[28];
} Elem;

void func_02035404(void *self)
{
    char *end;
    Elem *p;

    data_021c526c = self;
    end = (char *) self + 0x1c0;
    p = (Elem *) self;
    while ((char *) p < end) {
        func_020374ac(p);
        p++;
    }
    *(int *) ((char *) self + 0x1c0) = 0;
    func_020364ec((char *) self + 0x1c4);
    func_0203743c((char *) self + 0x24c);
    func_02036980((char *) self + 0x264);
    func_02036830((char *) self + 0x2a0);
    func_02035fc0((char *) self + 0x2b4);
    func_02035dc8((char *) self + 0x2d0);
    func_02035a6c((char *) self + 0x2e4);
    *(char *) ((char *) self + 0x2f4) = 0;
}
