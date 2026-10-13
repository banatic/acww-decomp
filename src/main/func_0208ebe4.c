/* func_0208ebe4 @ 0x0208ebe4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern __arm void func_020edb3c(void *);

struct UnkStruct_0208ebe4 {
    unsigned int unk_00;
    char pad_04[16];
    char sub14[20];
    char sub28[20];
};

extern unsigned char data_020e2330[];

struct UnkStruct_0208ebe4 *func_0208ebe4(struct UnkStruct_0208ebe4 *s)
{
    s->unk_00 = (unsigned int) data_020e2330;
    func_0208a1f4(&s->sub28);
    func_0208a1f4(&s->sub14);
    func_0208af00(s);
    func_020edb3c(s);
    return s;
}
