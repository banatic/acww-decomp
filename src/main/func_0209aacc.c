/* func_0209aacc @ 0x0209aacc, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ad9c(void *, int);
extern void *func_0209b4d4(void *object);
extern char *func_02137550(void *, int);
extern int func_02003704(int *);
extern int func_0207cb9c(void *, void **, int);
extern int func_0208150c(int);
extern int func_0209b4d8(int, int, int, int);
extern void func_02003728(void *, int);

typedef struct {
    char pad_00[0x60];
    int unk_60;
    char pad_64[0x70 - 0x64];
    int unk_70;
} UnkStruct_0209aacc;

extern unsigned char data_021e5a2c[];

void func_0209aacc(UnkStruct_0209aacc *p)
{
    void *local;
    int r5, r6;
    int x, y;

    r6 = func_0209ad9c(p, 0);
    func_0209b4d4((void *) r6);
    func_02137550(&local, 4);

    r5 = 0;
    if (func_02003704(&p->unk_60) != 0) {
        local = &p->unk_60;
        r5 = 1;
    }

    r5 = func_0207cb9c((void *) data_021e5a2c, &local, r5);
    x = func_0208150c(r5);
    func_0209b4d8(r6, 0xf, 0, x);
    y = func_0208150c(r5);
    p = (UnkStruct_0209aacc *) ((char *) p + 0x70);
    func_02003728(p, y);
}
