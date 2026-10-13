/* func_020726b8 @ 0x020726b8, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02072808(void);
extern void func_020725b4(void *p);
extern void func_020723a8(void *self);
extern void *data_021fbe94;
extern int func_020e9948(void *heap, int size);
extern int data_021d0484;
extern int data_021d047c;
extern int data_021d0470;
extern int data_021d0480;
extern void func_0203d228(void *p);
extern void func_020578ec(void *p);

typedef struct {
    unsigned char pad_00[0x38];
} ElemA;
typedef struct {
    unsigned char pad_00[0x2c4];
} ElemB;

void func_020726b8(void *self)
{
    void *heap;
    void *p1, *p2;
    ElemB *e1;
    ElemA *e2;
    unsigned int i;

    func_02072808();
    func_020725b4((char *) self + 4);
    func_020723a8(self);

    heap = data_021fbe94;

    p1 = (void *) func_020e9948(heap, 0x1620);
    data_021d0484 = (int) p1;

    p2 = (void *) func_020e9948(heap, 0x1c0);
    data_021d047c = (int) p2;

    e1 = (ElemB *) data_021d0484;
    e2 = (ElemA *) p2;
    for (i = 0; i < 8; i++) {
        if (e1 != 0) {
            func_0203d228(e1);
        }
        if (e2 != 0) {
            func_020578ec(e2);
        }
        e1 = (ElemB *) ((char *) e1 + 0x2c4);
        e2 = (ElemA *) ((char *) e2 + 0x38);
    }

    p1 = (void *) func_020e9948(heap, 0x1620);
    data_021d0470 = (int) p1;

    p2 = (void *) func_020e9948(heap, 0x1c0);
    data_021d0480 = (int) p2;

    e1 = (ElemB *) data_021d0470;
    e2 = (ElemA *) p2;
    for (i = 0; i < 8; i++) {
        if (e1 != 0) {
            func_0203d228(e1);
        }
        if (e2 != 0) {
            func_020578ec(e2);
        }
        e1 = (ElemB *) ((char *) e1 + 0x2c4);
        e2 = (ElemA *) ((char *) e2 + 0x38);
    }
}
