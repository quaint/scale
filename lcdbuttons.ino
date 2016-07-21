int readLcdButtons() {
  adcKeyIn = analogRead(0);      // read the value from the sensor
  if (adcKeyIn > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adcKeyIn < 50)   return btnRIGHT;
  if (adcKeyIn < 195)  return btnUP;
  if (adcKeyIn < 380)  return btnDOWN;
  if (adcKeyIn < 555)  return btnLEFT;
  if (adcKeyIn < 790)  return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}

void processLcdButtons() {
  lcd.setCursor(0, 0);           // move to the begining of the second line
  lcdKey = readLcdButtons();  // read the buttons
  boolean shouldPrint = false;
  if (lcdKey != btnNONE) {
    buttonPushed = lcdKey;
  } else if (buttonPushed != btnNONE) {
    switch (buttonPushed) {
      case btnRIGHT:
        selectedTrailer++;
        break;
      case btnLEFT:
        selectedTrailer--;
        break;
      case btnSELECT:
        printHeader = !printHeader;
        break;
      case btnUP:
        total = 0;
        break;
      case btnDOWN:
        shouldPrint = true;
        break;
    }
    buttonPushed = btnNONE;
  }
  delay(50);
  if (shouldPrint) {
    printRecipe(lastReadWeight, lastReadNumber);
  }
  if (selectedTrailer > trailersCount) {
    selectedTrailer = 0;
  } else if (selectedTrailer < 0) {
    selectedTrailer = trailersCount;
  }
  if (selectedTrailer == 0) {
    lcd.print(F("   0 kg"));
  } else {
    lcd.print(String(trailers[selectedTrailer]) + F(" kg"));
  }
  lcd.setCursor(12, 0);
  if (printHeader) {
    lcd.print(F("Logo"));
  } else {
    lcd.print(F("Brak"));
  }
  lcd.setCursor(0, 1);
  lcd.print(F("Suma "));
  lcd.setCursor(5, 1);
  lcd.print(String(total) + " kg       ");
}


