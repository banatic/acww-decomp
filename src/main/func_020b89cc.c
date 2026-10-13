/* func_020b89cc @ 0x020b89cc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d226c[];

typedef struct {
    int pad_00;
    char data[0x58];
} UnkStruct_020b89cc;

void func_020a8228(UnkStruct_020b89cc *s);
void func_020b4980(UnkStruct_020b89cc *s, unsigned char *b, int flag);
void func_0208aa48(char *dest, const UnkStruct_020b89cc *src);
void func_020a8210(UnkStruct_020b89cc *s);

struct SelfData {
    char pad_00[0x100];
    unsigned int unk_100;
};

void func_020b89cc(struct SelfData *self)
{
    unsigned char ch;
    UnkStruct_020b89cc local;
    char *p;

    ch = data_020d226c[self->unk_100];
    func_020a8228(&local);
    func_020b4980(&local, &ch, 0);
    p = (char *) self + 8;
    func_0208aa48(p, &local);
    func_020a8210(&local);
}
