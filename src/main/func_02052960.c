/* func_02052960 @ 0x02052960, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short f0 : 6;
    unsigned short f6 : 1;
    unsigned short f7 : 4;
    unsigned short f11 : 4;
} UnkStruct_02052960;
extern void func_0205298c(int a, int b, int c, int d, int e);
void func_02052960(UnkStruct_02052960 *p)
{
    func_0205298c((unsigned char) p->f0, p->f7, p->f11, (unsigned char) p->f6, 1);
}
