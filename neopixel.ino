void displayValue(unsigned long value) {
  int value4 = value % 10;
  value /= 10;
  int value3 = value % 10;
  value /= 10;
  int value2 = value % 10;
  value /= 10;
  int value1 = value % 10;
  value /= 10;
  int value0 = value % 10;
  boolean firstFound = false;
  if (value0 > 0) {
    digit(0, value0, COLOR_1);
    firstFound = true;
  } else {
    digit(0, value0, COLOR_0);
  }
  if (firstFound || value1 > 0) {
    digit(1, value1, COLOR_2);
    firstFound = true;
  } else {
    digit(1, value1, COLOR_0);
  }
  if (firstFound || value2 > 0) {
    digit(2, value2, COLOR_1);
    firstFound = true;
  } else {
    digit(2, value2, COLOR_0);
  }
  if (firstFound || value3 > 0) {
    digit(3, value3, COLOR_2);
    firstFound = true;
  } else {
    digit(3, value3, COLOR_0);
  }
  digit(4, value4, COLOR_1);
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

