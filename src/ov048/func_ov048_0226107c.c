/* func_ov048_0226107c @ 0x0226107c, 0x7c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a17ec(void);
extern int func_020a1810(void);
extern void func_ov048_02262378(void *);
extern void func_ov048_022616b8(void *, int);
extern void func_0206844c(void *, char *, void *);
extern void func_020c1874(void);
extern void *data_ov048_02263d20;

typedef struct {
    char pad_00[0x40];
    void *ptr;
    char pad_44[0x6a];
    unsigned char unk_AE;
    char pad_AF[0x762];
    unsigned char unk_811;
} UnkStruct_0226107c;

extern unsigned char data_ov048_02264704[];

void func_ov048_0226107c(UnkStruct_0226107c *this)
{
    char buf[2];
    void *r4 = this->ptr;
    if (func_020a17ec() != 0) {
        func_ov048_02262378(this);
        buf[0] = 10;
        func_0206844c(r4, buf, (void *) data_ov048_02264704);
        func_ov048_022616b8(this, 0);
    } else {
        if (func_020a1810() != 0) {
            this->unk_811 = 1;
            func_ov048_02262378(this);
            buf[1] = this->unk_AE;
            func_0206844c(r4, &buf[1], data_ov048_02263d20);
            func_020c1874();
            func_ov048_022616b8(this, 0);
        }
    }
}
