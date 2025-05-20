<p align="center">
  <img src="https://img.shields.io/badge/PASW%20Control-v1.0-blue.svg" alt="Version">
  <img src="https://img.shields.io/badge/license-MIT-green" alt="License">
  <img src="https://img.shields.io/badge/language-C%2B%2B-blue" alt="Language">
  <img src="https://img.shields.io/badge/webSockets-supported-yellow" alt="WebSockets">
</p>

# PASW Control

Turn your smartphone into a realistic steering wheel and pedal set for PC applications and games.

## Overview

PASW Control is a program that transforms your smartphone into a comprehensive steering wheel, pedal set, and customizable control panel for your PC. Users simply open a local web page on their phone—no additional apps required—and gain access to three high-response multi-touch sliders (clutch, brake, and throttle) and four button inputs which can be mapped on-the-fly. On the desktop side, the companion Qt application displays connection status, real‑time steering angle (via your phone’s gyroscope), and pedal values. Advanced settings allow you to adjust smoothing, linearity curves, and invert steering axis to suit your driving style.

## Table of Contents

* [🚀 Features](#-features)
* [📦 Tech Stack](#-tech-stack)
* [⚙️ Installation](#-installation)
* [🎮 Usage](#-usage)
* [🔧 Configuration](#-configuration)
* [🤝 Contributing](#-contributing)
* [📄 License](#-license)

## 🚀 Features

* **No App Download:** Works in any modern browser; no extra installation on your phone.
* **Multi-Touch Sliders:** Custom touch-enabled controls for clutch, brake, and throttle.
* **Configurable Buttons:** Four assignable buttons with on-the-fly mapping.
* **Gyroscope Steering:** Real-time steering data from your phone’s sensors via DeviceOrientation API.
* **Desktop Dashboard:** View connection status and live control data.
* **Adjustable Settings:** Smoothing, linearity curve, and inversion options for steering.
* **Open Source:** 100% transparent code—fork, modify, and contribute.
* **Lightweight & Simple:** Minimalist UI and straightforward setup.

## 📦 Tech Stack

| Component    | Technology                           |
| ------------ | ------------------------------------ |
| Desktop App  | Qt 6.9, C++17                        |
| Build System | QMake                                |
| Web Server   | Node.js, npm                         |
| Frontend     | HTML5, CSS3, JavaScript (WebSockets) |

## ⚙️ Installation

1. **Download setup from latest releases**

2. **Open setup, choose application installation folder, click "Next"**

3. **Click on "Create a desktop shortcut", then click "Next"**

4. **Click install**

5. **Follow "NodeJS Setup Wizard" and "vJoy Device Driver Setup Wizard"(Next just click "Next" and "Install")**

6. **DO NOT CHANGE ANY PATH OR CHECKBOXES, EXCEPT LICENSE AGREEMENT**

7. **Click "Finish"**

## 🎮 Usage

1. **Connecting**

   * Ensure both your PC and smartphone are on the same local network(same WIFI).
   * Run the desktop app first.
   * Open the displayed URL (e.g., `https://192.168.0.10:3003`) in your phone’s browser(Don`t use Safari).

2. **Controls**

   * **Sliders:** Clutch, Brake, Throttle (multi-touch enabled).
   * **Buttons:** Four customizable action buttons.
   * **Steering:** Tilt your phone to control the wheel.

3. **Live Dashboard**

   * Monitor connection status, slider values, and steering angle on your PC.

## 🔧 Configuration

In the desktop application settings, you can:

* **Smoothing (%):** Filter sensor noise (May slow down tilt sensitivity, be careful).
* **Linearity (%):** Adjust response curve.
* **Invert Steering:** Reverse steering direction.

## 🤝 Contributing

We welcome contributions!

1. Fork the repo
2. Create a feature branch (`git checkout -b feature/YourFeature`)
3. Commit your changes (`git commit -m 'Add awesome feature'`)
4. Push to the branch (`git push origin feature/YourFeature`)
5. Open a Pull Request

## 📄 License

Distributed under the MIT License. See [LICENSE](LICENSE) for details.
