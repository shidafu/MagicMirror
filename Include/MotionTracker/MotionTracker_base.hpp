/* \file MotionTracker_base.hpp
  \brief Motion Tracker from image list.
  \author Leon Contact: towanglei@163.com
  \copyright TMTeam
  \version 1.0
  \History:
	 Leon 2016/06/20 12:04 pack into *.hpp files.\n
*/
#pragma once
#ifndef MOTIONTRACKER_BASE
#define MOTIONTRACKER_BASE

#include <opencv2/core/utility.hpp> 
#include <opencv2/tracking.hpp>
#include <opencv2/highgui.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/// Algorithm Mod
#define TRACK_MIL       "MIL"
#define TRACK_BOOSTING  "BOOSTING"

/* \class MotionTracker : 
   \brief A lazy mode singleton class:LogTool£¬Initial debug tool will construct.
   \note
      Use like: 
	    LogTool::Initial("C\\log.log");//just call once anywhere.
		   :
	    WRITE_LOG(severity_level::error, "...");

   \author Leon Contact: towanglei@163.com
   \version 1.0
   \date 2016/06/20 19:29
*/
class MotionTracker
{
private:
	//bool initialized = false;
	//bool selectObject = false;
	Ptr<Tracker> tracker = (Tracker*)0;
public:
	~MotionTracker()
	{
		if (tracker != 0)
		{
			delete tracker;
			tracker = (Tracker*)0;
		}
	}
	/// MotionStatus
	enum MotionStatus 
	{
		Uninitialized=0,
		Initialized=1,
		Prepared=2
	};
	MotionStatus motionStatus = Uninitialized;
public:
	/// Initial MotionTracker.
	bool Initial(const char* algorithm)
	{
		try
		{
			if (tracker != 0)
			{
				delete tracker;
				tracker = (Tracker*)0;
			}
			Ptr<Tracker> tracker = Tracker::create(algorithm);
			if (tracker == 0)
			{
				BOOST_LOG_TRIVIAL(error) << "MotionTracker::Initia() failed";
				throw 0;
				return false;
			}
			motionStatus = Initialized;
			return true;
		}
		catch (int e)
		{
			BOOST_LOG_TRIVIAL(error) << "MotionTracker::Initia() failed";
			return false;
		}
		catch (...)
		{
			BOOST_LOG_TRIVIAL(error) << "MotionTracker::Initia() failed";
			return false;
		}
	};
	/// PreTrack MotionTracker.
	bool PreTrack(Mat& frameIn, Rect2d& rectIn)
	{
		try
		{
			if (motionStatus == Initialized)
			{
				//initializes the tracker 
				if (!tracker->init(frameIn, rectIn))
				{
					BOOST_LOG_TRIVIAL(warning) << "MotionTracker::PreTrack() failed";
					return false;
				}
				BOOST_LOG_TRIVIAL(info) << "x=" << rectIn.x << ",y=" << rectIn.y 
					<< ",width=" << rectIn.width << ",height=" << rectIn.height << ".";
				rectangle(frameIn, rectIn, Scalar(255, 0, 0), 2, 1);
				motionStatus = Prepared;
				return true;
			}
		}
		catch (int e)
		{
			BOOST_LOG_TRIVIAL(error) << "MotionTracker::Track() failed";
			return false;
		}
		catch (...)
		{
			BOOST_LOG_TRIVIAL(error) << "MotionTracker::Track() failed";
			return false;
		}
	};
	/// Track MotionTracker.
	bool Track(Mat& frameIn, Rect2d& rectOut)
	{
		try
		{
			if (motionStatus == Prepared)
			{
				//updates the tracker
				if (tracker->update(frameIn, rectOut))
				{
					BOOST_LOG_TRIVIAL(info) << "x=" << rectOut.x << ",y=" << rectOut.y
						<< ",width=" << rectOut.width << ",height=" << rectOut.height << ".";
					rectangle(frameIn, rectOut, Scalar(255, 0, 0), 2, 1);
					return true;
				}
			}
		}
		catch (int e)
		{
			BOOST_LOG_TRIVIAL(error) << "MotionTracker::Track() failed";
			return false;
		}
		catch (...)
		{
			BOOST_LOG_TRIVIAL(error) << "MotionTracker::Track() failed";
			return false;
		}
	};
};

#endif

