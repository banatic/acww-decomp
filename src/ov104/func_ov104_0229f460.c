/* func_ov104_0229f460 @ 0x0229f460, 0x110 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Handler)(void);

extern void *func_ov002_02207f80(unsigned int);
extern void func_ov002_0220830c(void);
extern void func_02066694(void *);
extern void func_020b9af4(void *);
extern void func_ov094_0229b000(void *);
extern void func_ov094_0229bc3c(void *);
extern void func_ov094_0229a2ec(void *);
extern void func_ov002_02207e40(void *);
extern void func_ov002_02209e44(void *);
extern void func_ov002_02209ccc(void *);
extern void func_ov002_02209b14(void *);
extern void func_ov002_0220ba24(void *);
extern void func_0206e388(void *);
extern void func_ov002_0220b47c(void *);
extern void func_ov002_0220b008(void *);
extern void func_02066688(void);
extern void func_02138d6c(void *, int, int, Handler, Handler);

extern char data_ov104_0229f6d0;

void *func_ov104_0229f460(void)
{
    void *obj;
    char *p;
    char *end;

    obj = func_ov002_02207f80(0x4380);
    if (obj == 0) {
        goto done;
    }

    func_ov002_0220830c();
    ((void **) obj)[0] = (void *) &data_ov104_0229f6d0;

    func_02066694((char *) obj + 0xc0);
    func_02066694((char *) obj + 0x1c0);

    p = (char *) obj + 0x2c0;
    end = (char *) obj + 0x2f8;
    do {
        func_020b9af4(p);
        p += 0x38;
    } while (p != end);

    func_ov094_0229b000(end);
    func_ov094_0229bc3c((char *) obj + 0xd58);
    func_ov094_0229a2ec((char *) obj + 0xd80);
    func_ov002_02207e40((char *) obj + 0x23b8);
    func_ov002_02209e44((char *) obj + 0x2488);
    func_ov002_02209ccc((char *) obj + 0x24a0);
    func_ov002_02209b14((char *) obj + 0x2504);
    func_ov002_0220ba24((char *) obj + 0x28f8);
    func_0206e388((char *) obj + 0x2a14);
    func_ov002_0220b47c((char *) obj + 0x2d3c);

    func_02138d6c((char *) obj + 0x2db4, 0xa, 0x100, (Handler) func_02066694, (Handler) func_02066688);
    func_02138d6c((char *) obj + 0x37b4, 0xa, 0x100, (Handler) func_02066694, (Handler) func_02066688);

    func_ov002_0220b008((char *) obj + 0x41b4);

done:
    return obj;
}
