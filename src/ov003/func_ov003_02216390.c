/* func_ov003_02216390 @ 0x02216390, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02216404(char *p, int byte, int *arr);
extern void func_ov003_02216400(char *p, int byte);
extern void func_020109a0(void *obj, int a, int b, int c);
extern int func_02073908(int a, int b);
extern void func_02035684(int a, int b, int c);
extern int data_020ccf94;

void func_ov003_02216390(void *obj, unsigned char *pData)
{
    unsigned char *p = &pData[0xc];
    int local[3];
    int e = p[2];
    int d = p[1];

    local[0] = pData[0xc];
    local[1] = d;

    func_ov003_02216404((char *) obj + 0x7d4, e, local);
    func_ov003_02216400((char *) obj + 0x8f0, e);
    func_020109a0(obj, 0x47, 3, 0);
    if (func_02073908(data_020ccf94, *(int *) ((char *) obj + 0x800))) {
        func_02035684(0x12, 0xf, 0);
    }
}
