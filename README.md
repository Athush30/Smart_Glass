# Bliss: Smart Glasses Project

Bliss is a project aimed at creating smart glasses with advanced functionalities to enhance user safety and convenience. This project integrates hardware and software to provide features like GPS tracking, emergency call support, and real-time traffic updates using Firebase and Arduino.

## Features

1. **Firebase Connectivity**  
   Firebase is used to manage real-time data, including:
   - Current height (`act_height`) of the glasses from the database.
   - Connection status of the device.

2. **Sensing Data**
   The smart glasses collect and monitor real-time sensing data, including:

   Height Data: Monitors the actual height of obstacles in the user's path.
   Obstacle Detection: Ensures safe navigation by detecting and alerting the user about obstacles ahead.

3. **Web Interface**  
   A sleek, responsive web interface for monitoring and controlling the glasses. Built with HTML, CSS, and JavaScript.

## Future implementations
1. **GPS Tracking**  
   The smart glasses include GPS functionality to track the user's location. In cases of emergencies, this data can be shared for assistance.

2. **Emergency Mode**  
   An emergency button triggers a call for help and notifies designated contacts.

3. **Camera Integration**  
   A camera is integrated to provide real-time visuals, allowing users to avoid traffic and navigate efficiently.

## Technologies Used

- **Hardware**: ESP32C3  
- **Backend**: Firebase (Realtime Database)  
- **Frontend**:  
  - HTML5  
  - CSS3  
  - JavaScript  

## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/Athush30/_bliss_.git
   ```

2. Set up the Firebase configuration in `script.js`:
   Replace the placeholder Firebase credentials with your own:
   ```javascript
   const firebaseConfig = {
       apiKey: "your-api-key",
       authDomain: "your-auth-domain",
       databaseURL: "your-database-url",
       projectId: "your-project-id",
       storageBucket: "your-storage-bucket",
       messagingSenderId: "your-messaging-sender-id",
       appId: "your-app-id"
   };
   ```

3. Open `home.html` in a browser to access the web interface.

4. Interact with the interface to monitor real-time data and use the functionalities of the smart glasses.

## Project Structure

```
_bliss_/
├── home.html       # Main HTML file for the web interface
├── script.js       # JavaScript file for interactivity and Firebase integration
├── styles.css      # Stylesheet for the web interface
└── README.md       # Project documentation
```

## Contributions

Contributions are welcome! Please fork this repository and create a pull request for any feature suggestions or improvements.

## License

This project is open-source and available under the MIT License.

