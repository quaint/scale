void printRecipe() {
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault();
  printer.setCodePage(CODEPAGE_ISO_8859_2);

  if (printHeader) {
    printer.printBitmap(logomale_width, logomale_height, logomale_data);
    printer.feed();
    printer.justify('C');
    printer.setSize('M');
    printer.println("Gospodarstwo Rolne");
    printer.justify('C');        
    printer.setSize('M');
    printer.print("Przemys");
    printer.write(0xb3);
    printer.print("aw Wi");
    printer.write(0xb6);
    printer.println("niewski");
    printer.justify('C');
    printer.setSize('S');
    printer.print(F("Os"));
    printer.write(0xf3);
    printer.println(F("wka 37"));
    printer.print(F("77-416 Tarn"));
    printer.write(0xf3);
    printer.println(F("wka"));
    printer.println(F("tel. 504 133 774"));
  }
  printer.feed();

  //  printer.println(data + F("             ") + godzina);
  printDate();
  
  printer.println(F("- - - - - - - - - - - - - - - -"));
  printer.justify('R');
  printer.setSize('S');
  //  printer.println(F("Waga"));
  if (selectedTrailer > 0) {
    printer.setSize('S');
    printer.println("Brutto " + lastReadWeight + " kg");
    printer.print(F("Tara "));
    printer.print(trailers[selectedTrailer]);
    printer.println(F(" kg"));
    printer.println(F("- - - - - - - - - - - - - - - -"));
    printer.setSize('L');
    //    printer.print(F("Netto "));
    int wagaInt = lastReadWeight.toInt();
    unsigned long netto = 0;
    if (wagaInt > trailers[selectedTrailer]) {
      netto = wagaInt - trailers[selectedTrailer];
      total += netto;
    }
    printer.print(netto);
    printer.println(F(" kg"));
  } else {
    printer.setSize('L');
    printer.println(lastReadWeight + F(" kg"));
  }
  printer.feed();
  printer.justify('L');
  printer.setSize('S');
  printer.println(lastReadNumber);
  printer.feed(4);
  printer.sleep();      // Tell printer to sleep
}

void printTotal(unsigned long totalSum) {
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault();
  printDate();
  printer.println(F("- - - - - - - - - - - - - - - -"));
  printer.justify('R');
  printer.setSize('L');
  printer.print(F("Suma "));
  printer.print(totalSum);
  printer.println(F(" kg"));
  printer.feed(4);
  printer.sleep();      // Tell printer to sleep  
}

void printDate() {
  DateTime now = rtc.now();
  if (now.day() < 10) {
    printer.print(0);
  }
  
  printer.print(now.day(), DEC);
  printer.print('.');
  if (now.month() < 10) {
    printer.print(0);
  }
  printer.print(now.month(), DEC);
  printer.print('.');
  printer.print(now.year(), DEC);
  printer.print(F("             "));
  if (now.hour() < 10) {
    printer.print(0);
  }
  printer.print(now.hour(), DEC);
  printer.print(':');
  if (now.minute() < 10) {
    printer.print(0);
  }
  printer.print(now.minute(), DEC);
  printer.print(':');
  if (now.second() < 10) {
    printer.print(0);
  }
  printer.print(now.second(), DEC);
  printer.println();
}
