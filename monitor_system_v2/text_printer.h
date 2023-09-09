#ifndef TEXT_PRINTER_H
#define TEXT_PRINTER_H
#define X_START 21
#define Y_START 32

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include "font.h"

enum notif_type {
  CLIMBING, CRYING, CRAWLING, SAFE, NC
};

const uint16_t notif_text_color[5] = {ST77XX_WHITE, ST77XX_WHITE, ST77XX_BLACK, ST77XX_WHITE, ST77XX_WHITE};
const uint16_t notif_bg_color[5] = {ST77XX_RED, ST77XX_RED, ST77XX_YELLOW, 0x04A0, 0xFBE0};

class TextPrinter {
  public:
  TextPrinter() {}
  TextPrinter(Adafruit_ST7789& tft, uint8_t font_size) : tft_(tft), font_size_(font_size) {}

  /*
   * Set the text content that is going to be print on the screen
   * Assumption the input: text is a string where words are separated
   * by single spaces.
   */
  void setText(char* text, uint8_t len) {
    memcpy(text_, text, len);
    text_len_ = len;
  }

  void setColorOfText(uint8_t nt) {
    text_color_idx_ = nt;
  }

  void printTextNaive() {
    for (int i = 0; i < min(text_len_, 64); ++i) {
      int row = i / 8, col = i % 8;
      drawASCIIChar(text_[i], X_START + col * 16, Y_START + row * 32);
    }
  }

  /*
   * print the text that is set to this class
   */
  void printText() {
    uint8_t cur_row = 0;
    for (uint8_t i = 0; i < text_len_; ++i) {
      uint8_t last_space_seen = i + 8, j = 0;
      // Go through the next 8 characters (8 characters per row)
      // Keep the index of the last space seen
      for (j = 0; j < 8 && i + j < text_len_; ++j) {
        if (text_[i + j] == ' ') {
          last_space_seen = i + j;
        }
      }
      uint8_t cur_line_print_until = last_space_seen;
      if (i + j >= text_len_ || text_[i + j] == ' ') {
        cur_line_print_until = i + j;
      } else {
        cur_line_print_until = last_space_seen;
      }
      uint8_t padding = (8 - (cur_line_print_until - i)) / 2;
      for (j = i; j < cur_line_print_until; ++j) {
        uint8_t row = cur_row, col = (j - i + padding);
        drawASCIIChar(text_[j], X_START + col * 16, Y_START + row * 32);
      }
      i = cur_line_print_until;
      cur_row++;
    }
  }

  /*
  * idx is the index of the character, and size represent the size of the pixels
  */
  void drawASCIIChar(uint16_t idx, uint16_t x_start, uint16_t y_start) {
    for (uint16_t i = 0; i < 16; ++i) {
      for (uint8_t j = 0; j < 8; ++j) {
        if (pgm_read_byte_near(ASCII_CHAR + idx * 16 + i) & (1 << (7 - j))) {
          for (uint8_t x = 0; x < font_size_; ++x) {
            for (uint8_t y = 0; y < font_size_; ++y) {
              tft_.drawPixel(x_start + j * font_size_ + x, y_start + i * font_size_ + y, notif_text_color[text_color_idx_]);
            }
          }
        }
      }
    }
  }
  private:
  Adafruit_ST7789& tft_;
  char text_[64];
  uint16_t c_x_;
  uint16_t c_y_;
  uint8_t text_len_;
  uint8_t font_size_;
  uint8_t text_color_idx_;
};

#endif