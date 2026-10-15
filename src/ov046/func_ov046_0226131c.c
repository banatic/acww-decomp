/* func_ov046_0226131c @ 0x0226131c, 0x5c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0226131c {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xc0 - 0x44];
    void *unk_C0;
} UnkStruct_0226131c;

extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void *func_020b1954(char *);
extern int func_020b1394(char *, void *);
extern void func_02068404(void *, int, char *);
extern void *func_020b193c(char *);
extern void func_0206844c(void *a, char *b, const void *c);
extern const int data_ov046_02261fe8;

void func_ov046_0226131c(UnkStruct_0226131c *this)
{
    void *o = this->unk_40;
    char code;
    int buf[8];

    code = 5;
    if (func_0206fbc0() == 0) {
        return;
    }
    if (func_0206fc6c() != 0) {
        code = 0x3d;
        func_020b1954((char *) buf);
        func_020b1394((char *) buf, this->unk_C0);
        func_02068404(this->unk_40, 0, (char *) buf);
        func_020b193c((char *) buf);
    }
    func_0206844c(o, &code, (const void *) &data_ov046_02261fe8);
}
