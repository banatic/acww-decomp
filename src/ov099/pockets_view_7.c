/* pockets_view_7: 3 functions, module ov099
 * mwccarm 1.2/base -O4,s
 * func_ov099_0229deb8 @ 0x0229deb8, 0xa0 bytes, Thumb
 * func_ov099_0229de98 @ 0x0229de98, 0x20 bytes, Thumb
 * func_ov099_0229de7c @ 0x0229de7c, 0x1a bytes, Thumb
 */

typedef struct UnkStruct_0229deb8 {
    unsigned char pad_00[0x38];
} UnkStruct_0229deb8;

typedef struct UnkStruct_0229deb8_2 {
    void *vtable;
    unsigned char pad_04[0x90];
    UnkStruct_0229deb8 sub[1];
} UnkStruct_0229deb8_2;

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *arg0);
extern void *func_020b9af4(void *p);
extern void *func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void *func_ov094_0229a2ec(void *p);
extern void *func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_02209b14(void *p);
extern void *func_ov002_0220ba24(void *p);
extern void func_02066694(void *p);
extern unsigned char data_ov099_0229e040[];
extern void func_ov099_0229d994(unsigned char *arg0);
extern void func_ov002_02208090(int, int);
extern unsigned char *func_ov002_022080a0(int, unsigned char value);
extern int func_020ee45c(void *arg0);
extern void func_ov092_0229929c(void *);
extern void func_ov099_0229d964(int);

void *func_ov099_0229deb8(void)
{
    UnkStruct_0229deb8_2 *p;
    UnkStruct_0229deb8 *q, *end;

    p = (UnkStruct_0229deb8_2 *) func_ov002_02207f80(0x2910);
    if (p != 0) {
        func_ov002_0220830c((void *) p);

        p->vtable = data_ov099_0229e040;

        q = &p->sub[0];
        end = &p->sub[1];
        do {
            func_020b9af4(q);
            q++;
        } while (q != end);

        func_ov094_0229b000(end);

        func_ov094_0229bc3c((char *) p + 0xb2c);
        func_ov094_0229a2ec((char *) p + 0xb54);
        func_ov002_02207e40((char *) p + 0x218c);
        func_ov002_02209e44((char *) p + 0x225c);
        func_ov002_02209ccc((char *) p + 0x2274);
        func_ov002_02209b14((char *) p + 0x22d8);
        func_ov002_0220ba24((char *) p + 0x26cc);
        func_02066694((char *) p + 0x2800);
    }

    return p;
}

int func_ov099_0229de98(int param)
{
    int r4 = param;
    func_ov099_0229d994((unsigned char *) param);
    func_ov002_02208090(r4, 0);
    func_ov002_022080a0(r4, 0);
    return 1;
}

int func_ov099_0229de7c(int p)
{
    func_ov092_0229929c((void *) func_020ee45c((void *) p));
    func_ov099_0229d964(p);
    return 1;
}
