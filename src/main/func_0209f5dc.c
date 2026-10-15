/* func_0209f5dc @ 0x0209f5dc, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0209f5dc {
    char pad_00[0x94];
    void *unk_94;
} UnkStruct_0209f5dc;

extern int func_02074150(void);
extern void func_02068358(void *);
extern void func_02068434(void *);
extern void func_020a6f20(int, int);
extern int func_020a6f00(void);
extern void func_020a6ef0(void *);
extern void func_0206844c(void *, unsigned char *, const void *);
extern void func_020a01e0(int);
extern void func_0209f820(UnkStruct_0209f5dc *, int);
extern void func_02074120(void);
extern unsigned char data_021f43e8;
extern const int data_020e37d0;

void func_0209f5dc(UnkStruct_0209f5dc *this)
{
    void *o = this->unk_94;
    int r = func_02074150();

    if ((unsigned int) (r - 5) <= 1) {
        func_02068358(o);
        func_02068434(o);
        if (r == 5) {
            func_020a6f20(0, 6);
            func_020a6ef0((void *) func_020a6f00());
            func_0206844c(o, &data_021f43e8, (const void *) 0);
            func_020a01e0(0);
            func_0209f820(this, 3);
        } else {
            unsigned char code = 5;
            func_0206844c(o, &code, (const void *) &data_020e37d0);
            func_0209f820(this, 2);
        }
        func_02074120();
    }
}
