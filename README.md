Overview:

This web application provides a live, visual display of a door's open/closed status. It polls a server every second for updates, dynamically changing the displayed image and color scheme to reflect the current state. The design is responsive, ensuring usability across various devices.

The Door Status Detector is a simple web interface that offers real-time monitoring of a door's condition. It operates by:

Continuously Fetching Data: Every second, the application retrieves the door's status from a server.
Visual Status Indicators:
The displayed door image changes to represent an open or closed door.
The background colors of the header, footer, and status display also change, providing clear visual cues.
Dynamic Updates: The user interface automatically updates to reflect any changes in the door's status.

# Door Status Detector

This application provides a real-time visual display of a door's open/closed status using Arduino, JavaScript, HTML, and CSS.

## Application Architecture and Functionality

### Arduino (Hardware & Data Acquisition)

* **Sensors:** An Arduino board is equipped with a sensor (e.g., a magnetic reed switch, a Hall effect sensor, or a simple limit switch) to detect the door's state.
* **Arduino Code (Arduino IDE):**
    * The Arduino code continuously monitors the sensor.
    * When the sensor detects a change in the door's state (open or closed), the Arduino sends this data to a connected device (likely a computer or a Raspberry Pi) via a communication protocol (e.g., serial communication, or if a network module is attached, then by using TCP/IP or UDP).
    * The Arduino code handles the sensor input and sends a simple message, like "OPEN" or "CLOSED" or numerical data like "1" or "0" through the serial port.

### Server-Side (Potentially a Computer or Raspberry Pi)

* **Serial Communication (if applicable):** If the Arduino is connected via serial, a server-side program (likely written in Python or Node.js) reads the data from the serial port.
* **Web Server (Node.js or Python Flask/Django):**
    * A web server is set up to handle requests from the web browser.
    * This server receives the door status data from the Arduino (either directly or through the serial communication program).
    * The server exposes an endpoint (e.g., `/status`) that provides the current door status in a format like JSON or plain text.
* **Data Storage (Optional):** The server might optionally store the door status history in a database or file.

### Client-Side (Web Browser)

* **HTML (Structure):** The HTML code defines the structure of the web page, including the door image, the status display, and the header/footer.
* **CSS (Styling):** CSS is used to style the web page, including the colors, fonts, and layout. It also handles the dynamic color changes based on the door's status.
* **JavaScript (Logic & Communication):**
    * JavaScript code runs in the web browser.
    * It uses `setInterval()` to repeatedly fetch the door status from the server's `/status` endpoint every second.
    * When the status is received, JavaScript updates the:
        * Door image (e.g., changes the `src` attribute of an `<img>` tag).
        * Background colors of the header, footer, and status display (e.g., changes the `style.backgroundColor` property).
        * It also updates the text that displays the current status.

### Connection

* The Arduino is connected to the server device.
* The server device is connected to the same network as the device that the browser is running on.

## Detailed Workflow

1.  **Sensor Trigger:** The door's state changes, triggering the Arduino sensor.
2.  **Arduino Data Transmission:** The Arduino sends the door status data to the server.
3.  **Server Data Reception:** The server receives and processes the data.
4.  **Web Request:** The JavaScript code in the browser sends a request to the server's `/status` endpoint.
5.  **Server Response:** The server sends the current door status to the browser.
6.  **JavaScript Update:** The JavaScript code updates the web page's elements based on the received status.
7.  **Visual Feedback:** The user sees the updated door image and colors.
8.  **Repeat:** Steps 4-7 repeat every second.
