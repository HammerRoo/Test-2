#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
//#include <opencv2/tracking.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <chrono>
#include <Windows.h>
#include <math.h>

using namespace std;
using namespace cv;

string getVideoPath()
{
    string videoPath;
    cout << "������� ���� � ����������: ";
    getline(cin, videoPath);
    return videoPath;
}

void displayControls()
{
    cout << "\n���������� �����:\n";
    cout << "E - ����� ������� ��� ������������ (������� ���� �� �����������)\n";
    cout << "������ - �����/���������� ���������������\n";
    cout << "A - ���������� ����� ����� �� 1 �������\n";
    cout << "D - ���������� ����� ������ �� 1 �������\n";
    cout << "W - ��������� ���������\n";
    cout << "S - ��������� ���������\n";
    cout << "Esc - �����\n";
}

void handleUserInput(VideoCapture& cap, bool& isPaused, int& volume)
{
    char key = waitKey(30);

    if (key == ' ')
    {
        isPaused = !isPaused;
    }
    else if (key == 'a' || key == 'A')
    {
        double currentPos = cap.get(CAP_PROP_POS_MSEC);
        cap.set(CAP_PROP_POS_MSEC, max(0.0, currentPos - 1000));
    }
    else if (key == 'd' || key == 'D')
    {
        double currentPos = cap.get(CAP_PROP_POS_MSEC);
        cap.set(CAP_PROP_POS_MSEC, currentPos + 1000);
    }
    else if (key == 'w' || key == 'W')
    {
        volume = min(100, volume + 1);
        cout << "���������: " << volume << "%" << endl;
    }
    else if (key == 's' || key == 'S')
    {
        volume = max(0, volume - 1);
        cout << "���������: " << volume << "%" << endl;
    }
    else if (key == 27)
    {
        exit(0);
    }
}

void playVideo(const string& videoPath)
{
    VideoCapture cap(videoPath);

    if (!cap.isOpened())
    {
        cout << "������: �� ������� ������� ����� �� ���� " << videoPath << endl;
        return;
    }

    Mat frame;
    bool isPaused = false;
    int volume = 50;

    while (true)
    {
        if (!isPaused)
        {
            cap >> frame;

            if (frame.empty())
            {
                cout << "����� ��������� ��� �� ������� ��������� ����." << endl;
                break;
            }

            imshow("��������������� �����", frame);
        }

        handleUserInput(cap, isPaused, volume);

        // �������������� �����, ����� ���� ����� ���������� ����
        if (isPaused)
        {
            waitKey(30);
        }
    }

    cap.release();
    destroyAllWindows();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    displayControls();

    string videoPath = getVideoPath();

    playVideo(videoPath);

    return 0;
}

// D:\videos\test1.mp4