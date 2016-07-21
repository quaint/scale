void displayValue(unsigned long value) {
  digit(4, value % 10, COLOR_4);
  value /= 10;
  digit(3, value % 10, COLOR_4);
  value /= 10;
  digit(2, value % 10, COLOR_4);
  value /= 10;
  digit(1, value % 10, COLOR_4);
  value /= 10;
  digit(0, value % 10, COLOR_4);
}

void digit(int position, int value, uint32_t color) {
  int begining = position * DIGIT_WIDTH;
  turnOnSevenSegments(begining, color);
  switch (value) {
    case 0:
      turnOffPixel(begining, 1, 2);
      break;
    case 1:
      turnOffPixel(begining, 1, 0);
      turnOffPixel(begining, 1, 2);
      turnOffPixel(begining, 1, 4);
      turnOffPixel(begining, 0, 0);
      turnOffPixel(begining, 0, 1);
      turnOffPixel(begining, 0, 2);
      turnOffPixel(begining, 0, 3);
      turnOffPixel(begining, 0, 4);
      break;
    case 2:
      turnOffPixel(begining, 0, 1);
      turnOffPixel(begining, 2, 3);
      break;
    case 3:
      turnOffPixel(begining, 0, 1);
      turnOffPixel(begining, 0, 3);
      break;
    case 4:
      turnOffPixel(begining, 1, 0);
      turnOffPixel(begining, 1, 4);
      turnOffPixel(begining, 0, 3);
      turnOffPixel(begining, 0, 4);
      break;
    case 5:
      turnOffPixel(begining, 2, 1);
      turnOffPixel(begining, 0, 3);
      break;
    case 6:
      turnOffPixel(begining, 2, 1);
      break;
    case 7:
      turnOffPixel(begining, 0, 1);
      turnOffPixel(begining, 0, 2);
      turnOffPixel(begining, 0, 3);
      turnOffPixel(begining, 0, 4);
      turnOffPixel(begining, 1, 2);
      turnOffPixel(begining, 1, 4);
      break;
    case 8:
      break;
    case 9:
      turnOffPixel(begining, 0, 3);
      break;
  }
}

void turnOffPixel(int begining, int x, int y) {
  if (y == 1 || y == 3) {
    pixels.setPixelColor((y + 1) * DISPLAY_WIDTH - 1 - begining - x, COLOR_0);
  } else {
    pixels.setPixelColor(y * DISPLAY_WIDTH + begining + x, COLOR_0);
  }
}

void turnOnSevenSegments(int begining, uint32_t color) {
  for (int i = 0; i < DIGIT_HEIGHT; i++) {
    if (i == 1 || i == 3) {
      int index = (i + 1) * DISPLAY_WIDTH - 1 - begining;
      pixels.setPixelColor(index, color);
      if (i != 1 && i != 3) {
        pixels.setPixelColor(index - 1, color);
      }
      pixels.setPixelColor(index - 2, color);
    } else {
      int index = i * DISPLAY_WIDTH + begining;
      pixels.setPixelColor(index, color);
      if (i != 1 && i != 3) {
        pixels.setPixelColor(index + 1, color);
      }
      pixels.setPixelColor(index + 2, color);
    }
  }
}

