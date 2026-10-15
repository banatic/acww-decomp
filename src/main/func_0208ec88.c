/* func_0208ec88 @ 0x0208ec88, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208af30(void *p);
extern void func_0208a1f8(void *p);
extern void *func_0208e95c(void *, int);
extern char data_020e2330;

typedef struct {
    void *unk_00;
    char pad_04[8];
    int unk_0C;
    int unk_10;
    unsigned char sub_14[20];
    unsigned char sub_28[20];
    int unk_3C;
    unsigned char unk_40;
    int unk_44;
} UnkStruct_0208ec88;

void *func_0208ec88(UnkStruct_0208ec88 *p, int v)
{
    func_0208af30(p);
    p->unk_00 = (void *) &data_020e2330;
    p->unk_0C = 0;
    p->unk_10 = 0;
    func_0208a1f8(p->sub_14);
    func_0208a1f8(p->sub_28);
    p->unk_3C = 0;
    p->unk_40 = v;
    p->unk_44 = -1;
    func_0208e95c(p, 0);
    return p;
}
