#include <stdint.h>
#include <display.h>
#include <pl110.h>

static struct pl110_mmio *pm = 0;
static uint16_t volatile *fb = 0;

static unsigned char g_8x8_font[2048] =
{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x7E, 0x81, 0xA5, 0x81, 0xBD, 0x99, 0x81, 0x7E,
        0x7E, 0xFF, 0xDB, 0xFF, 0xC3, 0xE7, 0xFF, 0x7E,
        0x6C, 0xFE, 0xFE, 0xFE, 0x7C, 0x38, 0x10, 0x00,
        0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x10, 0x00,
        0x38, 0x7C, 0x38, 0xFE, 0xFE, 0x92, 0x10, 0x7C,
        0x00, 0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x7C,
        0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00,
        0xFF, 0xFF, 0xE7, 0xC3, 0xC3, 0xE7, 0xFF, 0xFF,
        0x00, 0x3C, 0x66, 0x42, 0x42, 0x66, 0x3C, 0x00,
        0xFF, 0xC3, 0x99, 0xBD, 0xBD, 0x99, 0xC3, 0xFF,
        0x0F, 0x07, 0x0F, 0x7D, 0xCC, 0xCC, 0xCC, 0x78,
        0x3C, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x7E, 0x18,
        0x3F, 0x33, 0x3F, 0x30, 0x30, 0x70, 0xF0, 0xE0,
        0x7F, 0x63, 0x7F, 0x63, 0x63, 0x67, 0xE6, 0xC0,
        0x99, 0x5A, 0x3C, 0xE7, 0xE7, 0x3C, 0x5A, 0x99,
        0x80, 0xE0, 0xF8, 0xFE, 0xF8, 0xE0, 0x80, 0x00,
        0x02, 0x0E, 0x3E, 0xFE, 0x3E, 0x0E, 0x02, 0x00,
        0x18, 0x3C, 0x7E, 0x18, 0x18, 0x7E, 0x3C, 0x18,
        0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x66, 0x00,
        0x7F, 0xDB, 0xDB, 0x7B, 0x1B, 0x1B, 0x1B, 0x00,
        0x3E, 0x63, 0x38, 0x6C, 0x6C, 0x38, 0x86, 0xFC,
        0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x00,
        0x18, 0x3C, 0x7E, 0x18, 0x7E, 0x3C, 0x18, 0xFF,
        0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x00,
        0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x00,
        0x00, 0x18, 0x0C, 0xFE, 0x0C, 0x18, 0x00, 0x00,
        0x00, 0x30, 0x60, 0xFE, 0x60, 0x30, 0x00, 0x00,
        0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xFE, 0x00, 0x00,
        0x00, 0x24, 0x66, 0xFF, 0x66, 0x24, 0x00, 0x00,
        0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x00, 0x00,
        0x00, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00,
        0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00,
        0x18, 0x7E, 0xC0, 0x7C, 0x06, 0xFC, 0x18, 0x00,
        0x00, 0xC6, 0xCC, 0x18, 0x30, 0x66, 0xC6, 0x00,
        0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00,
        0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00,
        0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00,
        0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00,
        0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30,
        0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
        0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00,
        0x7C, 0xCE, 0xDE, 0xF6, 0xE6, 0xC6, 0x7C, 0x00,
        0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00,
        0x78, 0xCC, 0x0C, 0x38, 0x60, 0xCC, 0xFC, 0x00,
        0x78, 0xCC, 0x0C, 0x38, 0x0C, 0xCC, 0x78, 0x00,
        0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x1E, 0x00,
        0xFC, 0xC0, 0xF8, 0x0C, 0x0C, 0xCC, 0x78, 0x00,
        0x38, 0x60, 0xC0, 0xF8, 0xCC, 0xCC, 0x78, 0x00,
        0xFC, 0xCC, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00,
        0x78, 0xCC, 0xCC, 0x78, 0xCC, 0xCC, 0x78, 0x00,
        0x78, 0xCC, 0xCC, 0x7C, 0x0C, 0x18, 0x70, 0x00,
        0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00,
        0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30,
        0x18, 0x30, 0x60, 0xC0, 0x60, 0x30, 0x18, 0x00,
        0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00,
        0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00,
        0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00,
        0x7C, 0xC6, 0xDE, 0xDE, 0xDC, 0xC0, 0x7C, 0x00,
        0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00,
        0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00,
        0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00,
        0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00,
        0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00,
        0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00,
        0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3A, 0x00,
        0xCC, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00,
        0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
        0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00,
        0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00,
        0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00,
        0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00,
        0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00,
        0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00,
        0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00,
        0x7C, 0xC6, 0xC6, 0xC6, 0xD6, 0x7C, 0x0E, 0x00,
        0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00,
        0x7C, 0xC6, 0xE0, 0x78, 0x0E, 0xC6, 0x7C, 0x00,
        0xFC, 0xB4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0x00,
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00,
        0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00,
        0xC6, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0xC6, 0x00,
        0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x78, 0x00,
        0xFE, 0xC6, 0x8C, 0x18, 0x32, 0x66, 0xFE, 0x00,
        0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00,
        0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00,
        0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00,
        0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
        0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
        0xE0, 0x60, 0x60, 0x7C, 0x66, 0x66, 0xDC, 0x00,
        0x00, 0x00, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00,
        0x1C, 0x0C, 0x0C, 0x7C, 0xCC, 0xCC, 0x76, 0x00,
        0x00, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
        0x38, 0x6C, 0x64, 0xF0, 0x60, 0x60, 0xF0, 0x00,
        0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
        0xE0, 0x60, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00,
        0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
        0x0C, 0x00, 0x1C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78,
        0xE0, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x00,
        0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00,
        0x00, 0x00, 0xCC, 0xFE, 0xFE, 0xD6, 0xD6, 0x00,
        0x00, 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0x00,
        0x00, 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x00,
        0x00, 0x00, 0xDC, 0x66, 0x66, 0x7C, 0x60, 0xF0,
        0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0x1E,
        0x00, 0x00, 0xDC, 0x76, 0x62, 0x60, 0xF0, 0x00,
        0x00, 0x00, 0x7C, 0xC0, 0x70, 0x1C, 0xF8, 0x00,
        0x10, 0x30, 0xFC, 0x30, 0x30, 0x34, 0x18, 0x00,
        0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00,
        0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00,
        0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00,
        0x00, 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00,
        0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
        0x00, 0x00, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00,
        0x1C, 0x30, 0x30, 0xE0, 0x30, 0x30, 0x1C, 0x00,
        0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00,
        0xE0, 0x30, 0x30, 0x1C, 0x30, 0x30, 0xE0, 0x00,
        0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0x00,
        0x7C, 0xC6, 0xC0, 0xC6, 0x7C, 0x0C, 0x06, 0x7C,
        0x00, 0xCC, 0x00, 0xCC, 0xCC, 0xCC, 0x76, 0x00,
        0x1C, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
        0x7E, 0x81, 0x3C, 0x06, 0x3E, 0x66, 0x3B, 0x00,
        0xCC, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
        0xE0, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
        0x30, 0x30, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
        0x00, 0x00, 0x7C, 0xC6, 0xC0, 0x78, 0x0C, 0x38,
        0x7E, 0x81, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00,
        0xCC, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
        0xE0, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00,
        0xCC, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
        0x7C, 0x82, 0x38, 0x18, 0x18, 0x18, 0x3C, 0x00,
        0xE0, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
        0xC6, 0x10, 0x7C, 0xC6, 0xFE, 0xC6, 0xC6, 0x00,
        0x30, 0x30, 0x00, 0x78, 0xCC, 0xFC, 0xCC, 0x00,
        0x1C, 0x00, 0xFC, 0x60, 0x78, 0x60, 0xFC, 0x00,
        0x00, 0x00, 0x7F, 0x0C, 0x7F, 0xCC, 0x7F, 0x00,
        0x3E, 0x6C, 0xCC, 0xFE, 0xCC, 0xCC, 0xCE, 0x00,
        0x78, 0x84, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
        0x00, 0xCC, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
        0x00, 0xE0, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
        0x78, 0x84, 0x00, 0xCC, 0xCC, 0xCC, 0x76, 0x00,
        0x00, 0xE0, 0x00, 0xCC, 0xCC, 0xCC, 0x76, 0x00,
        0x00, 0xCC, 0x00, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8,
        0xC3, 0x18, 0x3C, 0x66, 0x66, 0x3C, 0x18, 0x00,
        0xCC, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x00,
        0x18, 0x18, 0x7E, 0xC0, 0xC0, 0x7E, 0x18, 0x18,
        0x38, 0x6C, 0x64, 0xF0, 0x60, 0xE6, 0xFC, 0x00,
        0xCC, 0xCC, 0x78, 0x30, 0xFC, 0x30, 0xFC, 0x30,
        0xF8, 0xCC, 0xCC, 0xFA, 0xC6, 0xCF, 0xC6, 0xC3,
        0x0E, 0x1B, 0x18, 0x3C, 0x18, 0x18, 0xD8, 0x70,
        0x1C, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00,
        0x38, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00,
        0x00, 0x1C, 0x00, 0x78, 0xCC, 0xCC, 0x78, 0x00,
        0x00, 0x1C, 0x00, 0xCC, 0xCC, 0xCC, 0x76, 0x00,
        0x00, 0xF8, 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0x00,
        0xFC, 0x00, 0xCC, 0xEC, 0xFC, 0xDC, 0xCC, 0x00,
        0x3C, 0x6C, 0x6C, 0x3E, 0x00, 0x7E, 0x00, 0x00,
        0x38, 0x6C, 0x6C, 0x38, 0x00, 0x7C, 0x00, 0x00,
        0x18, 0x00, 0x18, 0x18, 0x30, 0x66, 0x3C, 0x00,
        0x00, 0x00, 0x00, 0xFC, 0xC0, 0xC0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xFC, 0x0C, 0x0C, 0x00, 0x00,
        0xC6, 0xCC, 0xD8, 0x36, 0x6B, 0xC2, 0x84, 0x0F,
        0xC3, 0xC6, 0xCC, 0xDB, 0x37, 0x6D, 0xCF, 0x03,
        0x18, 0x00, 0x18, 0x18, 0x3C, 0x3C, 0x18, 0x00,
        0x00, 0x33, 0x66, 0xCC, 0x66, 0x33, 0x00, 0x00,
        0x00, 0xCC, 0x66, 0x33, 0x66, 0xCC, 0x00, 0x00,
        0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88,
        0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
        0xDB, 0xF6, 0xDB, 0x6F, 0xDB, 0x7E, 0xD7, 0xED,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0xF8, 0x18, 0x18, 0x18,
        0x18, 0x18, 0xF8, 0x18, 0xF8, 0x18, 0x18, 0x18,
        0x36, 0x36, 0x36, 0x36, 0xF6, 0x36, 0x36, 0x36,
        0x00, 0x00, 0x00, 0x00, 0xFE, 0x36, 0x36, 0x36,
        0x00, 0x00, 0xF8, 0x18, 0xF8, 0x18, 0x18, 0x18,
        0x36, 0x36, 0xF6, 0x06, 0xF6, 0x36, 0x36, 0x36,
        0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
        0x00, 0x00, 0xFE, 0x06, 0xF6, 0x36, 0x36, 0x36,
        0x36, 0x36, 0xF6, 0x06, 0xFE, 0x00, 0x00, 0x00,
        0x36, 0x36, 0x36, 0x36, 0xFE, 0x00, 0x00, 0x00,
        0x18, 0x18, 0xF8, 0x18, 0xF8, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xF8, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x1F, 0x00, 0x00, 0x00,
        0x18, 0x18, 0x18, 0x18, 0xFF, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x1F, 0x18, 0x18, 0x18,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
        0x18, 0x18, 0x18, 0x18, 0xFF, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x1F, 0x18, 0x1F, 0x18, 0x18, 0x18,
        0x36, 0x36, 0x36, 0x36, 0x37, 0x36, 0x36, 0x36,
        0x36, 0x36, 0x37, 0x30, 0x3F, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x3F, 0x30, 0x37, 0x36, 0x36, 0x36,
        0x36, 0x36, 0xF7, 0x00, 0xFF, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xFF, 0x00, 0xF7, 0x36, 0x36, 0x36,
        0x36, 0x36, 0x37, 0x30, 0x37, 0x36, 0x36, 0x36,
        0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
        0x36, 0x36, 0xF7, 0x00, 0xF7, 0x36, 0x36, 0x36,
        0x18, 0x18, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
        0x36, 0x36, 0x36, 0x36, 0xFF, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xFF, 0x00, 0xFF, 0x18, 0x18, 0x18,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0x36, 0x36, 0x36,
        0x36, 0x36, 0x36, 0x36, 0x3F, 0x00, 0x00, 0x00,
        0x18, 0x18, 0x1F, 0x18, 0x1F, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x1F, 0x18, 0x1F, 0x18, 0x18, 0x18,
        0x00, 0x00, 0x00, 0x00, 0x3F, 0x36, 0x36, 0x36,
        0x36, 0x36, 0x36, 0x36, 0xFF, 0x36, 0x36, 0x36,
        0x18, 0x18, 0xFF, 0x18, 0xFF, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0xF8, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x1F, 0x18, 0x18, 0x18,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
        0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
        0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x76, 0xDC, 0xC8, 0xDC, 0x76, 0x00,
        0x00, 0x78, 0xCC, 0xF8, 0xCC, 0xF8, 0xC0, 0xC0,
        0x00, 0xFC, 0xCC, 0xC0, 0xC0, 0xC0, 0xC0, 0x00,
        0x00, 0x00, 0xFE, 0x6C, 0x6C, 0x6C, 0x6C, 0x00,
        0xFC, 0xCC, 0x60, 0x30, 0x60, 0xCC, 0xFC, 0x00,
        0x00, 0x00, 0x7E, 0xD8, 0xD8, 0xD8, 0x70, 0x00,
        0x00, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x60, 0xC0,
        0x00, 0x76, 0xDC, 0x18, 0x18, 0x18, 0x18, 0x00,
        0xFC, 0x30, 0x78, 0xCC, 0xCC, 0x78, 0x30, 0xFC,
        0x38, 0x6C, 0xC6, 0xFE, 0xC6, 0x6C, 0x38, 0x00,
        0x38, 0x6C, 0xC6, 0xC6, 0x6C, 0x6C, 0xEE, 0x00,
        0x1C, 0x30, 0x18, 0x7C, 0xCC, 0xCC, 0x78, 0x00,
        0x00, 0x00, 0x7E, 0xDB, 0xDB, 0x7E, 0x00, 0x00,
        0x06, 0x0C, 0x7E, 0xDB, 0xDB, 0x7E, 0x60, 0xC0,
        0x38, 0x60, 0xC0, 0xF8, 0xC0, 0x60, 0x38, 0x00,
        0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00,
        0x00, 0x7E, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00,
        0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x7E, 0x00,
        0x60, 0x30, 0x18, 0x30, 0x60, 0x00, 0xFC, 0x00,
        0x18, 0x30, 0x60, 0x30, 0x18, 0x00, 0xFC, 0x00,
        0x0E, 0x1B, 0x1B, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0xD8, 0xD8, 0x70,
        0x18, 0x18, 0x00, 0x7E, 0x00, 0x18, 0x18, 0x00,
        0x00, 0x76, 0xDC, 0x00, 0x76, 0xDC, 0x00, 0x00,
        0x38, 0x6C, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
        0x0F, 0x0C, 0x0C, 0x0C, 0xEC, 0x6C, 0x3C, 0x1C,
        0x58, 0x6C, 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00,
        0x70, 0x98, 0x30, 0x60, 0xF8, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void pl110_put_pixel(uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t index = x + y * 640;
	if(color)
		fb[index] = 0x10 << (5 + 1) | 0xf << 5;
}

static int _x = 0;
static int _y = 0;

void pl110_putc(char c)
{
	if(c == '\n') {
		_x = 0;
		_y += 8;
		return;	
	}
	int cx, cy;
	int mask[8] = {1,2,4,8,16,32,64,128};
	uint8_t *glyph = g_8x8_font + (int)c * 8;

	for(cy = 0; cy < 8; cy ++)
		for(cx = 0; cx < 8; cx ++)
			pl110_put_pixel(_x+(8-cx), _y+cy, glyph[cy]&mask[cx]?1:0);

	_x += 8;
	if(_x > 640) {
		_x = 0;
		_y += 8;	
	}
}

void pl110_clear()
{
	/*for (int x = 0; x < (640 * 480) - 10; ++x)
		fb[x] = 0x1f << (5 + 6) | 0xf << 5;*/
}

struct display pl110_display = {
	.putc = pl110_putc,
	.flags = 2,
	.name = "PL110 video display",
};

void pl110_init()
{
	pm = (struct pl110_mmio *)PL110_IOBASE;
	pm->tim0 = 0x3f1f3f9c;
	pm->tim1 = 0x080b61df;
	pm->upbase = 0x200000;
	pm->control = 0x1829;
	fb = (uint16_t*)0x200000;

	_x = 0;
	_y = 0;

	display_register(&pl110_display);
}

