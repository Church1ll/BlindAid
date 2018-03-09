#include "DepthObstacleHandPosition.h"

using namespace std;
using namespace cv;
using namespace std::chrono;

namespace Vision
{
  namespace DepthObstacle
  {
    namespace HandPosition
    {
      HandPosition::HandPosition(IParameters *params, IData *input, IData *output) : Base(params, input, output)
      {

      }

      void HandPosition::Process()
      {
        steady_clock::time_point start = steady_clock::now();

        MaskShadows();
        FindHandPosition();
        SeparateRegions();
        FindMaxInRegions();
        MapVibrationValues();
      
        steady_clock::time_point end = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(end - start);
        cout << "[OBST-HP] Depth obstacles detected.\t(" << setw(5) << (int)(time_span.count() * 1000) << " ms)\n";
      }

      void HandPosition::FindHandPosition()
      {
        // TODO: detect position of hand
        // use blobfinder hardcoded to expected color and size range of dot on glove, and limit to lower third of frame.

        Mat handDotMask;
        inRange(*_input->GetHsvImage(), _params->GetHandPositionParams()->GetHandDotHsvRange(0), _params->GetHandPositionParams()->GetHandDotHsvRange(1), handDotMask);

        Ptr<SimpleBlobDetector> sbd = SimpleBlobDetector::create(_params->GetHandPositionParams()->GetHandDetectorParams());

        vector<KeyPoint> keyPoints;
        sbd->detect(*_input->GetDepthImage(), keyPoints);

        if (keyPoints.size() == 0)
          _output->SetHandPosition(Point(_input->GetDepthImage()->cols / 2, _input->GetDepthImage()->rows / 2));
        else
          _output->SetHandPosition(keyPoints.at(0).pt);
      }
    }
  }
}