/* func_0205ea60 @ 0x0205ea60, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[7];
    unsigned char buf[8];
    unsigned int unk_10;
    unsigned char pad_14[12];
    unsigned int *unk_20;
    unsigned char pad_24[4];
} UnkStruct_0205ea60;

typedef struct {
    unsigned int pad_00;
} GType;

extern GType data_021ca16c;

extern unsigned short *func_0205f100(GType *g, int byte);
extern int func_0205f024(GType *g, int byte);
extern int func_0205f64c(unsigned short *);
extern int func_0205f130(GType *g, int byte);
extern void func_02054cdc(void *);
extern void func_02056ffc(void *ptr);
extern void func_02060214(UnkStruct_0205ea60 *p);

void func_0205ea60(UnkStruct_0205ea60 *p)
{
    unsigned char byte;
    int r6;

    byte = p->unk_00;
    if (*func_0205f100(&data_021ca16c, byte) == 0xfff1) {
        goto common;
    }
    func_0205f024(&data_021ca16c, byte);
    r6 = func_0205f64c((unsigned short *) func_0205f100(&data_021ca16c, byte));
    if (r6 == 0x2b) {
        goto common;
    }
    func_02054cdc((void *) func_0205f130(&data_021ca16c, byte));
    if (r6 != 0x27) {
        goto common;
    }
    func_02056ffc((unsigned char *) p + 8);
    *p->unk_20 = p->unk_10;
common:
    p = (UnkStruct_0205ea60 *) ((unsigned char *) p + 0x28);
    func_02060214(p);
}
