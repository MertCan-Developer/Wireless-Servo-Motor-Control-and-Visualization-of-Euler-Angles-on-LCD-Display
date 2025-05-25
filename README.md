# Wireless-Servo-Motor-Control-and-Visualization-of-Euler-Angles-on-LCD-Display

In this project, F4 Discovery and F030 cards of stm32 brand were used. All settings and libraries have been adjusted according to these platforms. If you want to take this project and use it on your own platforms, you need to adapt the libraries used in the project to your own work.

Below is the connection diagram of this project. You can make the same connections on your own board or on a different processor by making some changes to this diagram.

![Kablosuz Sensör Verisi Toplama ve Görselleştirme Sistemi (Bluetooth Kontrollü Mini Gimbal Logger – LCD Versiyon)](https://github.com/user-attachments/assets/d2acd7d9-24fb-4b48-aabf-729946f834b3)

When you have finished making the connections it can be a bit complicated like this 😵‍💫

![WhatsApp Görsel 2025-05-25 saat 11 56 24_bf9e8c49](https://github.com/user-attachments/assets/b4a2753c-d8c7-40a5-9bda-f1605d7ba24d)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

The working logic of the system is as follows:

- Data in the format '$;---,---,---;!' is sent to the Bluetooth module via the Serial Bluetooth Terminal application over the phone. Here, the dollar sign represents the beginning, the exclamation mark represents the end and the parts separated by commas in the middle are the CCRx values of the PWM signals that control the servo-1 and servo-2 motors respectively. The data coming over Bluetooth is received with the interrupt of the UART, so that no data is missed.

- After receiving this packet in F030, servo-1 and servo-2 CCRx values are parsed and saved in a larger buffer to be sent to the F4 discovery board.

- The BNO055 sensor is also connected to the F030 board and continuously reads data in while(1). The read sensor data is also saved to the designated place in the large buffer. 

- The data read from the BNO055 sensor is sent to the F4 board continuously in while(1) at certain intervals even if no data is received via bluetooth.

- The data format of the 29 bytes of data to be sent to the F4 card is '$;S:----,----,----;M:---,---;!'. Here 'S' represents the sensor and 'M' represents the motor. '$' is the start character and '!' is the end character. The data read from the sensor in the format holds the Roll, Pitch and Heading angles respectively. The motor CCRx data from the Bluetooth module are servo-1 and servo-2 data respectively.

- The data format of the 29 bytes of data to be sent to the F4 board is '$;S:----,----,----,----;M:---,---;!'. Here 'S' represents the sensor and 'M' represents the motor. '$' is the start character and '!' is the end character. The data read from the sensor in the format holds the Roll, Pitch and Heading angles respectively. The motor CCRx data from the Bluetooth module are servo-1 and servo-2 data respectively.

- When this data package arrives at the F4 card, the data at the points specified in the package are parsed and sent to the relevant places.

- The CCRx values of the servo motors are taken from the packet, converted from 'char' type to 'int' type and written to the relevant register of the relevant servo motor.

- The Euler angles (Roll, Pitch, Heading) in the package and read from the BNO055 sensor are also sent to be written to the relevant places on the LCD screen.

- F4 Discovery or F030 boards do not support RS-485 protocol. For this reason, MAX481 RS485-TTL converter is used. The RE and DE pins are connected to each other and this connection is connected to any GPIO pin of the respective board.

- For this converter to be in transmit mode, the relevant GPIO pin must be set. In order for it to be in receive mode, it must be reset. For this reason, the GPIO pin on the F030 board is set and the GPIO pin on the F4 Discovery board is reset.

- In this way, data is received and transmitted. For this project, we can say that the F030 card carries out the task of data reception and verification, and the F4 Discovery card carries out the task of routing and processing the received and verified data to the relevant places. In other words, this is a distributed system that lightens the processing load.
