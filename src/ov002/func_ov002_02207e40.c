/* func_ov002_02207e40 @ 0x02207e40, 0x40 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208ade8(void *p, int n);
extern void func_0208aa38(void *p, int n);
extern void func_0208aa40(void *p);
extern char data_ov002_0220baa8[];

typedef struct {
    void *unk_00;
    char pad_04[0xc8];
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
} UnkStruct_02207e40;

void *func_ov002_02207e40(UnkStruct_02207e40 *p)
{
    unsigned char *q;

    func_0208ade8(p, 0);
    p->unk_00 = data_ov002_0220baa8;
    q = &p->b0;
    *q = 0;
    func_0208aa38(p, 1);
    func_0208aa40(p);
    q = &p->b1;
    *q = 0;
    q = &p->b2;
    *q = 0;
    return p;
}
