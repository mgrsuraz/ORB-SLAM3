#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<unistd.h> // for usleep
#include<opencv2/opencv.hpp>
#include<System.h>


using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << endl << "Usage: ./mono_live path_to_vocabulary path_to_settings" << endl;
        return 1;
    }

    // Load settings
    cv::FileStorage fsSettings(argv[2], cv::FileStorage::READ);
    if(!fsSettings.isOpened())
    {
        cerr << "ERROR: Cannot open settings file at: " << argv[2] << endl;
        return -1;
    }

    float fps = fsSettings["Camera.fps"];
    if(fps == 0) fps = 1.0;  // Default to 1 fps for low compute
    int wait_time = 1000.0 / fps;

    // Create SLAM system
    ORB_SLAM3::System SLAM(argv[1], argv[2], ORB_SLAM3::System::MONOCULAR, true);

    // Open camera
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
    {
        cerr << "ERROR: Cannot open camera." << endl;
        return -1;
    }

    // Setup frame saving and logging
    ofstream timestamp_log("frame_timestamps.txt");
    int frame_id = 0;

    // Main loop
    cv::Mat frame;
    while(true)
    {
        cap >> frame;
        if(frame.empty())
        {
            cerr << "ERROR: Blank frame grabbed." << endl;
            break;
        }

        // Get timestamp
        double timestamp = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();

        // Save frame to disk
        stringstream filename;
        filename << "frames/frame_" << setw(4) << setfill('0') << frame_id << ".png";
        cv::imwrite(filename.str(), frame);

        // Log timestamp
        timestamp_log << filename.str() << " " << fixed << setprecision(6) << timestamp << endl;

        // Run SLAM tracking
        SLAM.TrackMonocular(frame, timestamp);

        // Display the frame
        cv::imshow("Live Camera", frame);
        if(cv::waitKey(1) == 'q') break;  // 1 frame/sec, exit with 'q'
        usleep(1000000); // 2,000,000 microseconds = 2 seconds

        frame_id++;
    }

    // Clean up
    timestamp_log.close();
    SLAM.Shutdown();
    // Save camera trajectory
    std::cout << "Saving keyframe trajectory..." << std::endl;
    SLAM.SaveKeyFrameTrajectoryTUM("kf_mono_live.txt");    
    std::cout << "Saving full trajectory..." << std::endl;
    SLAM.SaveTrajectoryTUM("trajectory_mono_live.txt");
    return 0;
}

