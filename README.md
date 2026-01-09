# ORB-SLAM3 (Updated Version)

**Real-Time Visual SLAM with Monocular Camera — Updated Python/C++ Integration & Live Camera Support**

This repository is a customized and updated version of the original ORB-SLAM3 library developed by **UZ-SLAMLab**. ORB-SLAM3 is a state-of-the-art visual, visual-inertial, and multi-map SLAM system capable of tracking in real time and performing place recognition and loop closure detection.

The original project can be found here:
**[https://github.com/UZ-SLAMLab/ORB_SLAM3](https://github.com/UZ-SLAMLab/ORB_SLAM3)**

**Note**: Only the custom code that I added or modified is included in this GitHub repository. The full updated codebase, including all modified C++/Python files and configuration updates, is available in the following Google Drive link: **[https://drive.google.com/file/d/1eWUgCB8c9Hidf_X2DhI-G1IVvoJUMh6k/view?usp=sharing](https://drive.google.com/file/d/1eWUgCB8c9Hidf_X2DhI-G1IVvoJUMh6k/view?usp=sharing)**

---

## **What I Updated**

Since the original ORB-SLAM3 repository has not been actively maintained, I updated several components to ensure compatibility with modern toolchains and to enable real-time experimentation on my system.

### Updated Components

* Updated **C++ code** to work with modern compilers and Ubuntu 20.04/22.04 environments
* Updated **Python scripts** for compatibility with newer Python versions
* Resolved deprecated functions, build issues, and CMake compatibility
* Updated dependencies (OpenCV, Eigen, Pangolin) to recent stable versions

### Added New File

I added a new C++ file under:

```
/Examples/Monocular/main_live.cc
```

This new file:

* Captures **live camera feed**
* Runs **monocular ORB-SLAM3**
* Detects **loop closures**
* Displays real-time tracking and map visualization
* Logs trajectory data for analysis

This feature enables real-time SLAM without needing pre-recorded datasets.

---

## **System Used for Experiments**

All experiments were performed on:

* **Dell Inspiron 5570 (2017 model)**
* **Intel Core i7**
* **16 GB RAM**
* **Ubuntu 20.04 / 22.04 environment**
* **OpenCV, Pangolin, Eigen, CMake (updated versions)**
* **USB webcam / Built-in laptop camera**

The system was able to track in real time with loop closure detection successfully.

---

## **Installation**

### 1. Install Dependencies

```bash
sudo apt update
sudo apt install cmake g++ git libopencv-dev python3-dev python3-pip
sudo apt install libeigen3-dev libglew-dev libboost-all-dev
```

### 2. Install Pangolin

```bash
git clone https://github.com/stevenlovegrove/Pangolin.git
cd Pangolin
mkdir build && cd build
cmake ..
cmake --build .
sudo make install
```

### 3. Clone This Updated Repository

```bash
git clone https://github.com/<your-username>/ORB_SLAM3-Updated.git
cd ORB_SLAM3-Updated
chmod +x build.sh
```

### 4. Build ORB-SLAM3

```bash
./build.sh
```

---

## **Running the Live Monocular SLAM**

After building, you can run the live camera SLAM using:

```bash
./Examples/Monocular/main_live \
Vocabulary/ORBvoc.txt \
Examples/Monocular/Live.yaml
```

Make sure the `Live.yaml` file contains:

* Correct camera intrinsics
* Correct resolution
* Frame rate settings for your webcam

---

## **Running with a Video File**

Offline video experimentation can be run using:

```bash
./Examples/Monocular/mono_euroc \
Vocabulary/ORBvoc.txt \
Examples/Monocular/<your-config>.yaml \
path/to/video.mp4
```

---

## **Features**

* Real-time visual tracking
* Local and global bundle adjustment
* Map initialization for monocular camera
* Loop detection and closure
* Relocalization
* Live camera integration (custom addition)
* Trajectory logging for evaluation

---

## **Trajectory Logging**

The system outputs:

* **Keyframe trajectory (`KeyFrameTrajectory.txt`)**
* **Camera trajectory (`CameraTrajectory.txt`)**

You can plot and analyze trajectories using Python, MATLAB, or evo.

---

## **Experimental Notes**

* Live loop closures were successfully detected using the updated live camera module.
* Real-time performance achieved on a mid-range 2017 laptop demonstrates the efficiency of ORB-SLAM3.
* Tested with indoor/outdoor scenes, medium lighting, and fast camera motion.

---

## **Project Structure (Key Additions)**

```
Examples/
 └── Monocular/
      ├── mono_euroc.cc
      ├── mono_tum.cc
      ├── mono_kitti.cc
      ├── main_live.cc     <-- (Newly added for live camera SLAM)
      ├── Live.yaml
```

---

## **Credits**

* Original ORB-SLAM3 by **UZ-SLAMLab**
  [https://github.com/UZ-SLAMLab/ORB_SLAM3](https://github.com/UZ-SLAMLab/ORB_SLAM3)
* Additional modifications and live camera integration by **Suraj Thapa**

---

## **License**

This project follows the original ORB-SLAM3 license (GPLv3).
Please review the `LICENSE` file for more details.
