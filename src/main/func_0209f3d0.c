/* func_0209f3d0 @ 0x0209f3d0, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0209f3d0 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[4];
    void *unk_48;
} UnkStruct_0209f3d0;

extern int func_0206837c(void *);
extern int func_020ab504(int);
extern void func_02068440(void *);
extern void func_02068364(void *, int);
extern void func_0209f820(void *, int);
extern void func_0206844c(void *, unsigned char *, const void *);
extern unsigned char data_021f43e8;
extern const int data_020e37d0;

void func_0209f3d0(UnkStruct_0209f3d0 *this)
{
    void *o = this->unk_40;
    int ok = func_020ab504(func_0206837c(o));
    unsigned char code;

    switch (this->unk_1E) {
        case 4:
            switch (ok) {
                case 0:
                    func_02068440(o);
                    func_02068364(o, 1);
                    func_0209f820(this->unk_48, 4);
                    break;
                case 1:
                    code = 8;
                    func_0206844c(o, &code, (const void *) &data_020e37d0);
                    break;
            }
            break;
        case 8:
            switch (ok) {
                case 0:
                    func_02068440(o);
                    func_02068364(o, 1);
                    func_0209f820(this->unk_48, 5);
                    break;
                case 1:
                    func_0206844c(o, &data_021f43e8, (const void *) 0);
                    break;
            }
            break;
        case 0:
            if (ok == 0) {
                func_0206844c(o, &data_021f43e8, (const void *) 0);
                func_0209f820(this->unk_48, 3);
            }
            break;
    }
}
