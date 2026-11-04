/* sound_scene_5: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f4338 @ 0x020f4338, 0x6c bytes, ARM
 * func_020f4318 @ 0x020f4318, 0x20 bytes, ARM
 * func_020f4314 @ 0x020f4314, 0x4 bytes, ARM
 */

extern int data_021fd1bc;
extern void func_020f1ecc(void *, int unused1);
extern int func_020f1d84(void *, int);
extern int func_020eec48(void);
extern void func_020eec60(int argument0);

int func_020f4338(unsigned char *p, unsigned int code)
{
    int v;
    switch (code) {
        case 0:
        case 4:
            v = 0x85;
            break;
        case 1:
        case 3:
            v = 0x86;
            break;
        case 2:
            v = 0x87;
            break;
        default:
            break;
    }
    func_020f1ecc(&data_021fd1bc, code);
    func_020f1d84(&data_021fd1bc, v);
    {
        int result = 1;
        p[6] = result;
        return result;
    }
}

void func_020f4318(unsigned char *r4)
{

    func_020eec60(func_020eec48());
    r4[6] = 0;
}

void func_020f4314(void *receiver, int a, int b) {}
