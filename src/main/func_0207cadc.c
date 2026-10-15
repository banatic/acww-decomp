/* func_0207cadc @ 0x0207cadc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x7EC];
} UnkStruct_0207cadc;

extern unsigned int func_0208150c(UnkStruct_0207cadc *p);
extern int func_02003704(void *);

int func_0207cadc(UnkStruct_0207cadc *p)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < 8; i++) {
        if (func_02003704((void *) func_0208150c(p))) {
            count++;
        }
        p++;
    }
    return count;
}
