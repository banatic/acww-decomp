/* func_020767ac @ 0x020767ac, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_020736bc(void *, unsigned char *, int);
extern void func_020786d8(int *, unsigned char *, unsigned char *, unsigned char *);
extern int func_0207cec0(void *, int);
extern void func_0207f1c8(int);
extern void *func_0209b5e8(void);
extern void *func_0209b91c(void *);
extern int func_0209bd44(void *);
extern void func_0209bb90(void *, int);
extern void func_0209ba7c(void *);
extern void func_0209b920(void *);
extern void func_0209b8a4(void *, int);
extern void func_0209b890(void *, int);

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char buf[2];
    int word;
} UnkStruct_020767ac;

extern unsigned char data_021e5a2c[];

void func_020767ac(void)
{
    UnkStruct_020767ac local;
    void *r4;
    void *base;
    int result;

    local.unk_00 = 6;
    local.unk_01 = 0;

    func_020736bc(data_020ccf94, local.buf, 2);
    func_020786d8(&local.word, &local.unk_00, &local.unk_01, local.buf);

    base = (void *) data_021e5a2c;
    result = func_0207cec0(base, local.word);
    if (result == 0) {
        return;
    }

    func_0207f1c8(result);

    r4 = func_0209b5e8();

    switch (local.unk_00) {
        case 0:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                func_0209bb90(func_0209b91c(r4), local.unk_01);
            }
            break;
        case 1:
            func_0209ba7c(r4);
            break;
        case 2:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                func_0209b920(r4);
            }
            break;
        case 3:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                func_0209b8a4(r4, local.unk_01);
            }
            break;
        case 4:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                func_0209b890(r4, local.unk_01);
            }
            // fallthrough
        case 5:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                *((unsigned char *) r4 + 0x2e) = local.unk_01;
            }
            break;
    }
}
