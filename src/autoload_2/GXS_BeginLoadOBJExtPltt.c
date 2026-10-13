/* GXS_BeginLoadOBJExtPltt @ 0x020e9918, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef enum {
    GX_VRAM_A = 0x0001,
    GX_VRAM_B = 0x0002,
    GX_VRAM_C = 0x0004,
    GX_VRAM_D = 0x0008,
    GX_VRAM_E = 0x0010,
    GX_VRAM_F = 0x0020,
    GX_VRAM_G = 0x0040,
    GX_VRAM_H = 0x0080,
    GX_VRAM_I = 0x0100,
    GX_VRAM_ALL = 0x01ff
} GXVRam;

typedef enum { GX_VRAM_SUB_OBJEXTPLTT_NONE = 0x0000, GX_VRAM_SUB_OBJEXTPLTT_0_I = GX_VRAM_I } GXVRamSubOBJExtPltt;

GXVRamSubOBJExtPltt GX_ResetBankForSubOBJExtPltt(void);

void GXS_BeginLoadOBJExtPltt(void);

extern GXVRamSubOBJExtPltt sSubOBJExtPltt;

void GXS_BeginLoadOBJExtPltt()
{
    ((void) 0);
    sSubOBJExtPltt = GX_ResetBankForSubOBJExtPltt();
    ((void) 0);
}
