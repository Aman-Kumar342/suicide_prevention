# Project: Comprehensive Human State Analysis

This project is a multi-faceted system designed to analyze a person's physical and emotional state through a combination of computer vision and sensor technology. It integrates three core modules:

1.  **Emotion Recognition**: A deep learning model that analyzes facial expressions to detect emotions like happiness, sadness, anger, etc.
2.  **Posture Detection**: A real-time system that uses computer vision to track body posture and identify slouching.
3.  **Smart Footbed**: An Arduino-powered insole with pressure sensors to analyze gait and foot pressure, determining phases like "Heel Strike" and "Foot Flat."

The goal is to create a holistic view of a person's well-being, which could have applications in healthcare, ergonomics, sports science, and human-computer interaction.

---

## Table of Contents

1.  [System Overview](#system-overview)
2.  [Technology Stack](#technology-stack)
3.  [Module 1: Emotion Recognition](#module-1-emotion-recognition)
    * [How it Works](#how-it-works-emotion)
    * [Setup & Training](#setup--training-emotion)
    * [Prediction](#prediction-emotion)
4.  [Module 2: Posture Detection](#module-2-posture-detection)
    * [How it Works](#how-it-works-posture)
    * [Setup & Usage](#setup--usage-posture)
5.  [Module 3: Smart Footbed](#module-3-smart-footbed)
    * [Hardware Required](#hardware-required-footbed)
    * [How it Works](#how-it-works-footbed)
    * [Setup & Usage](#setup--usage-footbed)
6.  [Full System Integration & Usage](#full-system-integration--usage)
7.  [Future Work & Customization](#future-work--customization)

---

## System Overview

The system works by running three parallel processes:
* The **Smart Footbed** (Arduino) continuously reads pressure data and sends it to a computer via a USB serial connection.
* The **Posture Detection** script (Python/MediaPipe) analyzes the user's body posture via a webcam.
* The **Emotion Recognition** model (Python/Keras) can be used to analyze images or video frames for emotional content.

A central Python application (to be developed) would be responsible for receiving the data from all three sources, interpreting it, and providing a unified output or logging the data for later analysis.

## Technology Stack

* **Programming Languages**: Python, C++ (for Arduino)
* **Frameworks & Libraries**:
    * **Deep Learning**: Keras / TensorFlow
    * **Computer Vision**: OpenCV, MediaPipe
    * **Data Handling**: Pandas, NumPy
* **Hardware**: Arduino (or compatible microcontroller), Pressure Sensors (FSRs), Webcam

---

## Module 1: Emotion Recognition

This module uses a Convolutional Neural Network (CNN) to classify facial expressions into one of seven emotions.

### How it Works (Emotion)

1.  **Data Collection**: The model is trained on a dataset of images, each labeled with an emotion (e.g., 'angry', 'happy', 'sad').
2.  **Preprocessing**: Images are converted to grayscale, resized to 48x48 pixels, and normalized. Labels are one-hot encoded.
3.  **CNN Architecture**: The model consists of multiple convolutional layers (for feature extraction), max-pooling layers (for down-sampling), and dropout layers (to prevent overfitting). Finally, dense layers perform the classification.
4.  **Training**: The model is trained on the preprocessed data. The trained model (weights and architecture) is saved to `emotiondetector.h5` and `emotiondetector.json` files.

### Setup & Training (Emotion)

1.  **Prerequisites**: Install Python and the required libraries.
    ```bash
    pip install tensorflow keras pandas numpy scikit-learn
    ```
2.  **Dataset**: You need a dataset of facial expression images, organized into subdirectories by emotion (e.g., `/train/happy`, `/train/sad`, etc.). The provided code points to a Google Drive directory, which you must replace with your local path.
3.  **Update Paths**: In `facerecognition.py`, change the `dir_train` and `dir_test` variables to point to your dataset location.
4.  **Run Training**: Execute the script. This will take time as it processes images and trains the neural network.
    ```bash
    python facerecognition.py
    ```

### Prediction (Emotion)

After training, the script can predict the emotion in a new image. Modify the `image` variable at the end of the script to point to an image file you want to analyze.

---

## Module 2: Posture Detection

This module uses Google's MediaPipe library to perform real-time pose estimation and classify posture.

### How it Works (Posture)

1.  **Pose Estimation**: MediaPipe identifies 33 body landmarks from the webcam feed.
2.  **Angle Calculation**: The script calculates the angle between the **left shoulder**, **left ear**, and **left hip**. This angle is a good indicator of upper body slouch.
3.  **Classification**: A simple threshold on the angle determines the posture status (e.g., "Happy" for good posture, "Sad" for slumped).
4.  **Visualization**: The output video shows the user with an overlay of the pose skeleton and the current posture status.

### Setup & Usage (Posture)

1.  **Prerequisites**: Install the necessary Python libraries.
    ```bash
    pip install opencv-python mediapipe numpy
    ```
2.  **Run the Script**:
    ```bash
    python posture_detection.py
    ```
3.  **Operation**: A window will open showing your webcam feed with real-time posture analysis. Press 'q' to quit.

---

## Module 3: Smart Footbed

This module uses an Arduino and pressure sensors to detect different phases of a person's gait.

### Hardware Required (Footbed)

* Arduino board (e.g., Uno, Nano)
* 6 x Force-Sensitive Resistors (FSRs) or other pressure sensors
* 6 x 10kΩ Resistors (for the voltage divider circuit with FSRs)
* Breadboard and jumper wires

### How it Works (Footbed)

1.  **Sensor Reading**: The Arduino reads analog voltage values from six pressure sensors placed in a shoe insole. The reading (0-1023) corresponds to the amount of pressure on the sensor.
2.  **Gait Analysis**: A series of `if-else` conditions analyzes the combination of pressure readings to determine the current state of the foot (e.g., "No pressure", "Heel Strike", "Foot Flat", "Heel Off").
3.  **Serial Communication**: The Arduino sends the raw sensor data and the determined gait phase to the connected computer over the USB serial port.

### Setup & Usage (Footbed)

1.  **Wiring**: Connect each FSR to an analog input pin on the Arduino using a voltage divider circuit.
2.  **Upload Code**:
    * Open the `Smart_Footbed_Code.ino` file in the Arduino IDE.
    * Select your board and port from the "Tools" menu.
    * Click the "Upload" button.
3.  **View Output**:
    * With the Arduino connected, open the Serial Monitor in the Arduino IDE (Tools > Serial Monitor).
    * Set the baud rate to 9600.
    * You will see the sensor readings and the detected gait phase printed every 200 milliseconds.

---

## Full System Integration & Usage

To run the full system, you would:

1.  **Start the Smart Footbed**: Connect the Arduino to your computer. The `Smart_Footbed_Code.ino` sketch should already be uploaded.
2.  **Run the Posture Detector**: Execute the `posture_detection.py` script to begin real-time posture analysis.
3.  **Develop a Master Script**: Create a new Python script that:
    * Reads serial data from the Arduino using a library like `pyserial`.
    * Integrates the logic from the posture and emotion detection scripts (likely by refactoring them into functions).
    * Presents a unified dashboard or logs all the data streams (gait, posture, emotion) into a single file (e.g., a CSV) for comprehensive analysis.

---

## Future Work & Customization

* **Integrated Dashboard**: Use a library like `Tkinter`, `PyQt`, or a web framework like `Flask` to create a graphical user interface that displays all data streams in real-time.
* **Advanced Classification**: Replace the simple `if-else` logic in the posture and gait analysis with more sophisticated machine learning models for higher accuracy.
* **Data Logging**: Implement robust data logging to save time-stamped sensor and analysis data for offline review and research.
* **Alerts & Feedback**: Trigger alerts (sound or visual) when poor posture is detected for an extended period.
