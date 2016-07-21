void processOutput() {
  String outputString = String(outbound);
  //  Serial.println(outputString);
  String numer = outputString.substring(2, 12);
  numer.trim();
  lastReadNumber = numer;
  //String data = outputString.substring(13, 23);
  //String godzina = outputString.substring(24, 32);
  String waga = outputString.substring(49, 57);
  waga.trim();
  lastReadWeight = waga;
  //  Serial.println(numer + " " + data + " " + godzina + " " + waga + "kg");
  displayValue(waga.toInt());
  pixels.show();
}
