void connectToWifi() {
  printTop("Connecting");
  printBot("to WiFi......");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // CBA to validate certs
  client.setInsecure();
}

void fetchStats() {
  printLoading();

  if (!client.connect(host, httpsPort)) {
    printTop("connection");
    printBot("failed");
    return;
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: Arduino\r\n" +
               "Connection: close\r\n\r\n");

  String line;

  // Pass headers
  while (client.connected()) {
    line = client.readStringUntil('\n');

    // Parse date header to get current time
    const char* headerName = "date:";
    if (line.startsWith(String(headerName))) {
      short dateStart = strlen(headerName);
      short timeStart = dateStart + 17;

      // 17 chars to start of time from the end of the "Date: " prefix
      dateStr = line.substring(dateStart, timeStart);
      dateStr.trim();

      String timeStr = line.substring(timeStart, timeStart + 9);
      timeStr.trim();
      hours = timeStr.substring(0, 2).toInt();
      mins = timeStr.substring(3, 5).toInt();
      seconds = timeStr.substring(6, 8).toInt();
    }
    if (line == "\r") break;
  }

  String content;

  while (client.available()) {
    content = client.readString();
  }

  Serial.println(content);

  parse(content.c_str());

  if (isDst) {
    hours++;
  }
}
