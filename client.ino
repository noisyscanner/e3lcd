void connectToWifi() {
  printTop("Connecting");
  printBot("to WiFi......");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //  Serial.println("");
  //  Serial.println("WiFi connected");
  //  Serial.println("IP address: ");
  //  Serial.println(WiFi.localIP());

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

  client.print(String("GET ") + url + "?year=" + String(currentYear) + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: Arduino\r\n" +
               "Connection: close\r\n\r\n");

  String line;

  // Pass headers
  while (client.connected()) {
    line = client.readStringUntil('\n');

    // Parse date header to get current time
    const char* headerName = "Date:";
    if (line.startsWith(String(headerName))) {
      // 17 chars to start of time
      short start = strlen(headerName) + 17;
      String dateStr = line.substring(start, start + 9);
      dateStr.trim();
      hours = dateStr.substring(0, 2).toInt();
      mins = dateStr.substring(3, 5).toInt();
    }
    if (line == "\r") break;
  }

  String content;

  while (client.available()) {
    content = client.readString();
  }

  parse(content.c_str());
}
