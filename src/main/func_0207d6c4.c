/* func_0207d6c4 @ 0x0207d6c4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021e5a2c;
extern int memcmp(const void *, const void *, unsigned int);
extern void *func_0207b410(const void *);
extern void *func_0209a774(void *);
extern int func_0208150c(int);
extern int func_02003704(void *);
extern int func_0207f150(int);

typedef struct {
    unsigned short unk_00;
    unsigned char unk_02[12];
    unsigned char unk_0E;
    unsigned char unk_0F;
} SampleStruct;

int func_0207d6c4(int a)
{
    SampleStruct *p5;
    SampleStruct *p4;
    int result;

    p5 = (SampleStruct *) func_0208150c(a);
    result = 0;
    if (func_02003704(p5) != 0) {
        if (func_0207f150(a) == 3) {
            p4 = (SampleStruct *) func_0209a774(func_0207b410(&data_021e5a2c));
            if (p5->unk_00 == p4->unk_00 && memcmp(p5->unk_02, p4->unk_02, 12) == 0 && p5->unk_0F == p4->unk_0F) {
                // empty
            } else {
                result = 1;
            }
        }
    }
    return result;
}
