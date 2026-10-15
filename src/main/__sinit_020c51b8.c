/* __sinit_020c51b8 @ 0x020c51b8, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char unk_00[0x10];
    int unk_10;
    int unk_14;
    unsigned char p1[0xc];
} El;
typedef struct {
    unsigned char unk_00[0x34];
    int unk_34, unk_38, unk_3C, unk_40;
    El arr[16];
} Big;
typedef struct {
    unsigned char unk_00[0x14];
    int unk_14;
    int unk_18;
    unsigned char p1[8];
} El2;

extern void __register_global_object(void *, void *, void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_0204b160(void *);

extern unsigned char data_021c779c;
extern void func_0204b184(void *);
extern unsigned char data_021c777c;
extern Big data_021c79c4;
extern unsigned char data_021c79dc;
extern void *func_0204b170(void *);
extern unsigned char data_021c7770;
extern El2 data_021c7c48[3];
extern unsigned char data_021c77c0;
extern void func_020012e0(void *);

void __sinit_020c51b8(void)
{
    Big *p;
    El *q;
    El2 *r;
    __register_global_object((void *) ((void *) &data_021c779c), (((void *) func_0204b184)),
                             (void *) ((void *) &data_021c777c));
    p = &data_021c79c4;
    func_0204b160((void *) &data_021c79dc);
    p->unk_34 = 0;
    p->unk_38 = 0;
    p->unk_3C = 0;
    p->unk_40 = 0;
    q = p->arr;
    do {
        q->unk_10 = 0;
        q->unk_14 = 0;
        q++;
    } while (q != p->arr + 16);
    __register_global_object((void *) ((void *) &data_021c79c4), (((void *) func_0204b170)),
                             (void *) ((void *) &data_021c7770));
    r = data_021c7c48;
    do {
        r->unk_14 = 0;
        r->unk_18 = 0;
        r++;
    } while (r != data_021c7c48 + 3);
    __cxa_vec_ctor((void *) ((void *) &data_021c77c0), 0x18, 8, (void (*)(void *)) func_020012e0, 0);
}
