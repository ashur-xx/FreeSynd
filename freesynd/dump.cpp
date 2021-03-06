
#include "screen.h"
#include "spritemanager.h"
#include "file.h"
#include <png.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


class App : public Singleton<App> {
public:
    App();
};

int margin = 100;
int screen_width = margin + 100;
int screen_height = margin + 100;
png_byte **screen_data = NULL;
png_color palette[256];

int lowest_row = 10000;
int highest_row = -10000;
int lowest_col = 10000;
int highest_col = -10000;

int write_png(int a, int f = -1) {
    char tmp[100];

    if (f != -1)
        sprintf(tmp, "anims/%04i%04i.png", a, f);
    else
        sprintf(tmp, "sprites/%i.png", a);

    FILE *fp = fopen(tmp, "wb");

    if (!fp) {
        printf("cannot write to %s\n", tmp);
        return 1;
    }

    png_structp png_ptr = png_create_write_struct(
            PNG_LIBPNG_VER_STRING, 0, 0, 0);

    if (!png_ptr) {
        printf("cannot create png write struct\n");
        return 1;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);

    if (!info_ptr) {
        printf("cannot create png info struct\n");
        return 1;
    }

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, screen_width, screen_height, 8,
            PNG_COLOR_TYPE_PALETTE, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_set_PLTE(png_ptr, info_ptr, palette, 256);

    png_write_info(png_ptr, info_ptr);

    png_write_image(png_ptr, screen_data);

    png_write_end(png_ptr, info_ptr);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(fp);

    return 0;
}

void clear_screen() {
    for (int i = 0; i < screen_height; i++)
        memset(screen_data[i], 255, screen_width);
}

int main(int argc, char **argv) {
    App *app = new App();
    Screen *screen = new Screen(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    GameSpriteManager sprites;

    screen_data = (png_byte**) calloc(1, sizeof(png_byte *) * screen_height);

    for (int i = 0; i < screen_height; i++)
        screen_data[i] = (png_byte*) calloc(1, sizeof(png_byte) * screen_width);

    int palsize;
    uint8 *pal = File::loadFile("hpal02.dat", palsize);
    assert(palsize == 768);

    for (int i = 0; i < palsize / 3; ++i) {
        uint8 r = pal[i * 3 + 0];
        uint8 g = pal[i * 3 + 1];
        uint8 b = pal[i * 3 + 2];

        palette[i].red = (r << 2) | (r >> 4);
        palette[i].green = (g << 2) | (g >> 4);
        palette[i].blue = (b << 2) | (b >> 4);
    }

    sprites.load();

    mkdir("anims", 0755);
    mkdir("sprites", 0755);

    for (int s = 0; s < sprites.spriteCount(); s++) {
        clear_screen();
        sprites.drawSpriteXYZ(s, 0, 0, 0);
        int tw = screen_width;
        int th = screen_height;
        screen_width = sprites.sprite(s)->width();
        screen_height = sprites.sprite(s)->height();
        if (screen_width != 0 && screen_height != 0)
            write_png(s);
        screen_width = tw;
        screen_height = th;
    }

    for (int a = 0; a < sprites.numAnims(); a++) {
        for (int f = 0; ; f++) {
            clear_screen();
            sprites.drawFrame(a, f, margin, margin);
            write_png(a, f);

            if (sprites.lastFrame(a, f))
                break;
        }
    }

    printf("row: lo %i high %i\n", lowest_row, highest_row);
    printf("col: lo %i high %i\n", lowest_col, highest_col);

    delete screen;
    delete app;
    return 0;
}

App::App() {

}

Screen::Screen(int width, int height) {

}

Screen::~Screen() {

}

void Screen::blit(int x, int y, int width, int height, const uint8 *pixeldata,
        bool flipped, int stride) {
    width_ = screen_width;
    height_ = screen_height;

    if (x + width < 0 || y + height < 0 || x >= width_ || y >= height_)
        return;

    int dx = x < 0 ? 0 : x;
    int dy = y < 0 ? 0 : y;

    int sx = x < 0 ? -x : 0;
    int sy = y < 0 ? -y : 0;

    int w = x < 0 ? x + width : x + width > width_ ? width_ - x : width;
    int h = y < 0
        ? y + height : y + height > height_ ? height_ - y : height;

    stride = (stride == 0 ? width : stride);
    int ofs = flipped ? w - 1 : 0;
    int inc = flipped ? -1 : 1;

    for (int j = 0; j < h; ++j) {
        if (dy + j < lowest_row)
            lowest_row = dy + j;

        if (dy + j > highest_row)
            highest_row = dy + j;

        if (dx + ofs < lowest_col)
            lowest_col = dx + ofs;

        if (dx + ofs > highest_col)
            highest_col = dx + ofs;

        uint8 *d = screen_data[dy + j] + dx + ofs;
        const uint8 *s = pixeldata + (sy + j) * stride + sx;

        for (int i = 0; i < w; ++i) {
            uint8 c = *s++;

            if (c != 255)
                *d = c;

            d += inc;
        }
    }
}

void Screen::scale2x(int x, int y, int width, int height,
        const uint8 *pixeldata, int stride, bool transp) {

}
