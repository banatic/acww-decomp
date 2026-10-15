/* func_0208f0c4 @ 0x0208f0c4, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int a;
    int b;
} Pair8;

typedef struct {
    char pad_00[0x18];
    int unk_18;
    char sub1[0x14];
    char sub2[0x14];
    int unk_44;
    char pad_48[0x28];
    unsigned short unk_70;
    char pad_72[3];
    unsigned char unk_75;
} UnkStruct_0208f0c4;

extern unsigned char data_020d0b74[];
extern int data_020d0b94[];
extern int data_020d0b84[];
extern Pair8 data_020d6fcc[];
extern void func_0208a1f0(void *sub, Pair8 *p);
extern void func_0208a1ec(void *sub, int v);
extern void *func_0208a144(void *sub);
extern void *func_0208a1e8(void *sub, int v);
extern void func_0208effc(UnkStruct_0208f0c4 *s);
extern void func_0208f014(UnkStruct_0208f0c4 *s);

void func_0208f0c4(UnkStruct_0208f0c4 *s, int k)
{
    int kx = k * 4;
    int idx = data_020d0b74[s->unk_18] + *(int *) ((char *) data_020d0b94 + kx);
    int idx2 = idx + 1;
    int v = *(int *) ((char *) data_020d0b84 + kx);

    s->unk_44 = k;
    func_0208a1f0(&s->sub1, &data_020d6fcc[idx]);
    func_0208a1ec(&s->sub1, v);
    func_0208a144(&s->sub1);
    func_0208a1f0(&s->sub2, &data_020d6fcc[idx2]);
    func_0208a1ec(&s->sub2, v);
    func_0208a144(&s->sub2);
    if (k == 1) {
        func_0208a1e8(&s->sub1, 0);
        func_0208a1e8(&s->sub2, 0);
    }
    if (k == 0) {
        func_0208effc(s);
    } else {
        func_0208f014(s);
        s->unk_70 = (s->unk_44 == 2) ? 0x7d5f : 0x50c0;
        s->unk_75 = 1;
    }
}
