/* screen_mark: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208ee14 @ 0x0208ee14, 0xc bytes, Thumb
 * func_0208ee10 @ 0x0208ee10, 0x2 bytes, Thumb
 * func_0208ee00 @ 0x0208ee00, 0x10 bytes, Thumb
 * func_0208edf0 @ 0x0208edf0, 0x10 bytes, Thumb
 * func_0208edb8 @ 0x0208edb8, 0x38 bytes, Thumb
 * func_0208ed98 @ 0x0208ed98, 0x20 bytes, Thumb
 * func_0208ed60 @ 0x0208ed60, 0x38 bytes, Thumb
 * func_0208ed40 @ 0x0208ed40, 0x20 bytes, Thumb
 * func_0208ecd0 @ 0x0208ecd0, 0x70 bytes, Thumb
 */

typedef struct {
    char pad_00[12];
    char unk_0C[20];
    int unk_20;
} UnkStruct_0208ed98;

typedef struct UnkStruct_0208ed60 {
    char pad_00[0xc];
    char unk_0C[0x14];
    int unk_20;
} UnkStruct_0208ed60;

extern unsigned int data_021d35f8[9];
extern void func_0208ee20(void *arg);
extern void func_0208eea0(void *);
extern void func_0208a1f0(void *, void *);
extern void func_0208a1ec(void *, int);
extern void *func_0208a144(void *);
extern int data_020d5b4c;
extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
extern int data_020d5b54;
extern unsigned int data_021c8c9c;
extern int func_0203ec98(void);
extern int func_020b65c4(void);
extern int func_020960d8(int);

int func_0208ecd0(void);

void func_0208ee14(void)
{
    data_021d35f8[8] = 0;
}

void func_0208ee10(void) {}

void func_0208ee00(void)
{
    func_0208ee20((void *) ((unsigned char *) data_021d35f8));
}

void func_0208edf0(void)
{
    (&func_0208eea0)(((char *) data_021d35f8));
}

void func_0208edb8(void *arg)
{
    int result = func_0208ecd0();
    if (result) {
        *(int *) ((char *) arg + 0x20) = 1;
        func_0208a1f0((char *) arg + 0xC, &data_020d5b4c);
        func_0208a1ec((char *) arg + 0xC, 1);
        func_0208a144((char *) arg + 0xC);
    }
}

void func_0208ed98(UnkStruct_0208ed98 *p)
{
    func_0208a0c8(p->unk_0C);
    if (func_0208a160(p->unk_0C)) {
        p->unk_20 = 2;
    }
}

void func_0208ed60(UnkStruct_0208ed60 *arg)
{
    if (func_0208ecd0()) {
        return;
    }
    arg->unk_20 = 3;
    func_0208a1f0(arg->unk_0C, &data_020d5b54);
    func_0208a1ec(arg->unk_0C, 1);
    arg = (UnkStruct_0208ed60 *) &arg->unk_0C;
    func_0208a144(arg);
}

void func_0208ed40(void *param)
{
    func_0208a0c8((char *) param + 0xc);
    if (func_0208a160((char *) param + 0xc) != 0) {
        *(int *) ((char *) param + 0x20) = 0;
    }
}

int func_0208ecd0(void)
{
    unsigned int a = (data_021c8c9c == 0);
    unsigned int b = (func_0203ec98() == 0);
    unsigned int c = (func_020b65c4() == 6);
    unsigned int x = func_020960d8(4);
    unsigned int d = (x - 8) <= 7;
    unsigned int e = (x - 0x24) <= 8;

    if (a != 0 && b != 0 && c == 0 && d == 0 && e == 0) {
        return 1;
    } else {
        return 0;
    }
}
