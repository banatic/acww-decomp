/* func_020285d0 @ 0x020285d0, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int x);
extern unsigned int func_020036e8(unsigned int x);
extern int func_0202da38(void *a, unsigned char *b, unsigned char *c, int d, int base, int offset, int scale, int h, int i);

typedef struct {
    unsigned char pad_00[0xC8];
    unsigned int word_at_c8;
    unsigned int word_at_cc;
    unsigned char pad_D0[0x30];
    unsigned int *ptr_at_100;
    unsigned char data_at_104[0x1E];
    unsigned char byte_at_122;
} UnkStruct_020285d0;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020285d0_2;

typedef struct {
    unsigned int word;
    unsigned char byte;
} GlobalC8C40;

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} GlobalD9130;

extern GlobalC8C40 data_020c8c40;
extern GlobalD9130 data_020d9130;

void func_020285d0(UnkStruct_020285d0 *a, UnkStruct_020285d0_2 *b)
{
    func_0202da38(a, a->data_at_104, &a->byte_at_122, 0x1e,
                  func_020036e8(func_0208150c(*(unsigned int *) ((char *) a->ptr_at_100 + 0x830))), data_020c8c40.word,
                  data_020c8c40.byte, 0, 0);
    b->ptr = a->data_at_104;
    b->byte = a->byte_at_122;
    *(GlobalD9130 *) &a->word_at_c8 = data_020d9130;
}
