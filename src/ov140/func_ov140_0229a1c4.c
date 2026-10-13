/* func_ov140_0229a1c4 @ 0x0229a1c4, 0x80 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x23];
} Elem;

typedef struct {
    unsigned char pad_00[0x180];
    Elem arr[32];
} ElemContainer;

typedef struct {
    unsigned char pad_00[0xa8];
    int unk_A8;
    unsigned char pad_AC[0x8b5 - 0xac];
    unsigned char unk_8B5[32];
    unsigned char pad_8D5[0x8dd - 0x8d5];
    unsigned char unk_8DD;
    unsigned char unk_8DE;
    unsigned char unk_8DF;
} Main;

extern ElemContainer *func_ov140_0229a15c(void *);
extern int func_ov140_0229a1a4(void *, void *);
extern void func_ov140_0229a020(void *);
extern void func_ov140_0229a078(void *);
extern void func_ov140_02299fc8(void *);

void func_ov140_0229a1c4(Main *r5)
{
    ElemContainer *r7;
    int count;
    int i;

    r7 = func_ov140_0229a15c(r5);
    count = 0;
    i = count;

    for (; i < 32; i++) {
        if (func_ov140_0229a1a4(r5, &r7->arr[i]) != 0) {
            count++;
        }
        r5->unk_8B5[i] = i;
    }

    r5->unk_8DD = 0;
    r5->unk_8DE = 5;
    r5->unk_8DF = count;

    func_ov140_0229a020(r5);
    func_ov140_0229a078(r5);
    func_ov140_02299fc8(r5);

    if (r5->unk_8DE != 0) {
        r5->unk_A8 = 8;
    }
}
