/* func_020161e4 @ 0x020161e4, 0x198 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *a, int k);
extern void func_0201a7b8(void *p, int r);

void func_020161e4(void *a, char *b)
{
    int v, r;

    v = func_020164a0(a, 0);
    r = 0;
    switch (v) {
        case 0x45:
        case 0x47:
        case 0x49:
        case 0x4b:
        case 0x4d:
        case 0x4f:
        case 0x51:
        case 0x53:
        case 0x55:
        case 0x57:
        case 0x59:
        case 0x5b:
        case 0x5d:
        case 0x5f:
        case 0x61:
        case 0x63:
        case 0x65:
        case 0x67:
        case 0x69:
        case 0x6e:
        case 0x70:
        case 0x72:
        case 0x75:
        case 0x77:
        case 0x79:
        case 0x7b:
        case 0x7c:
        case 0x7f:
        case 0x80:
        case 0x81:
        case 0x84:
        case 0x86:
        case 0x88:
        case 0x8a:
        case 0x8c:
        case 0x8d:
        case 0x8f:
        case 0x91:
        case 0x93:
        case 0x94:
        case 0x97:
        case 0x98:
        case 0x99:
        case 0x9c:
        case 0x9f:
        case 0xa1:
        case 0xa3:
        case 0xa5:
        case 0xa7:
        case 0x144:
            r = 2;
            break;
        case 0x46:
        case 0x48:
        case 0x4c:
        case 0x4e:
        case 0x50:
        case 0x52:
        case 0x54:
        case 0x56:
        case 0x5a:
        case 0x60:
        case 0x62:
        case 0x64:
        case 0x68:
        case 0x6c:
        case 0x6d:
        case 0x71:
        case 0x76:
        case 0x78:
        case 0x83:
        case 0x85:
        case 0x87:
        case 0x8b:
        case 0x96:
        case 0x9b:
        case 0x9d:
        case 0x9e:
        case 0xa0:
        case 0xa2:
        case 0xa4:
        case 0xa8:
        case 0xe6:
        case 0xea:
            r = 1;
            break;
    }
    func_0201a7b8(b + 0x418, r);
}
