# Acquiring and storing temperatures with Arduino and a DS18B20 sensor

- Acquiring temperature data every 6 minutes. 
- Store the data into an EPROM Array. Sore 3 days of data on 512 bytes of EPROM.
- Api to communicate with a Windows Console to
    - resetData
    - getData: Send acquired data as CSV to the WindowsConsole (Serial port)
    - acquireData
- Use fArduino library to write clean and readable code

- User interface on the arduino:
    Use on board led, to express that the application state:
    1) if blinking on/off every 1/2 second, the application is waiting, normal state
    2) if blinking on/off for 1.6 second quickly, the application just acquire a new temperature
    3) if blinking on/off for 4 seconds semi-quickly repeatedly, There is an issue with the sensor

