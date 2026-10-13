/* func_ov118_0229c9e0 @ 0x0229c9e0, 0xb0 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void);
extern void func_020b9cfc(void *p);
extern void func_02138d6c(void *a, int b, int c, void *d, void *e);
extern void func_ov002_0220a5fc(void *p);
extern void func_ov002_02209ccc(void *p);
extern void func_ov117_0229a2f0(void *p);
extern char data_ov118_0229cc08;
extern void func_02070c08(void);
extern void func_02070be8(void);
extern void func_ov118_0229a438(void);
extern void func_ov118_0229a43c(void);

void *func_ov118_0229c9e0(void)
{
    void *o;
    char *p;
    char *end;
    int c;

    o = func_ov002_02207f80(0x47d8);
    if (o != 0) {
        func_ov002_0220830c();
        *(void **) o = (void *) &data_ov118_0229cc08;

        p = (char *) o + 0xb4;
        end = (char *) o + 0xfc;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);

        func_02138d6c(end, 13, 0x6c, (void *) func_02070c08, (void *) func_02070be8);
        func_ov002_0220a5fc((char *) o + 0x678);
        func_ov002_02209ccc((char *) o + 0x6c0);
        func_ov117_0229a2f0((char *) o + 0x4724);

        c = 3;
        func_02138d6c((char *) o + 0x47a4, c, c, (void *) func_ov118_0229a43c, (void *) func_ov118_0229a438);
        func_02138d6c((char *) o + 0x47ad, 14, 3, (void *) func_ov118_0229a43c, (void *) func_ov118_0229a438);
    }

    return o;
}
