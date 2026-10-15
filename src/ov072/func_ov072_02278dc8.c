/* func_ov072_02278dc8 @ 0x02278dc8, 0x138 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern char data_021ebcd2;
extern char data_ov072_02279a00;

extern int func_02019c20(void *, int, int, int, int, int);
extern void func_0201b38c(void *, int);
extern int func_020164a0(void *, int);
extern int func_02019de8(void *);
extern int func_0201c2c8(void *, int);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_02019e00(void *);
extern void func_0208716c(char *);
extern int func_020155cc(void *);
extern int func_0202ea80(int, int);
extern int func_020644cc(int);
extern void func_0206844c(void *, char *, char *);
extern void func_ov072_02278f00(void *, int);

typedef struct {
    char pad_00[4];
    int unk_04;
} inner40;

typedef struct {
    char pad_00[0x40];
    inner40 *unk_40;
    char pad_44[0x70];
    unsigned char state;
    char pad_B5[0x7];
    char *unk_BC;
} outer;

void func_ov072_02278dc8(outer *p)
{
    switch (p->state) {
        case 0:
            if (p->unk_40->unk_04 == 5) {
                func_02019c20(p->unk_BC + 0x564, 2, 0xd5, 1, data_020c80f8, 0);
                func_0201b38c(p->unk_BC + 0x2a0, 0);
                p->state++;
            }
            break;
        case 1:
            if (func_020164a0(p->unk_BC + 0x334, 0) == 0xd5) {
                if (func_02019de8(p->unk_BC + 0x564) != 0) {
                    int res;
                    res = func_0201c2c8(p->unk_BC, 4);
                    func_02019d0c(p->unk_BC + 0x564, 3, 2, 0, 0, 0, res, 0, 0, data_020c80f8, 0);
                    p->state++;
                }
            }
            break;
        case 2:
            if (func_02019e00(p->unk_BC + 0x564) == 3) {
                if (func_02019de8(p->unk_BC + 0x564) != 0) {
                    unsigned char b;
                    func_0208716c(&data_021ebcd2);
                    func_020155cc(p);
                    func_0202ea80(0x14, 1);
                    b = (unsigned char) (func_020644cc(5) + 5);
                    func_0206844c(p->unk_40, (char *) &b, &data_ov072_02279a00);
                    func_ov072_02278f00(p, 0);
                }
            }
            break;
    }
}
