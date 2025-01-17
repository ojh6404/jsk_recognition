// -*- mode: C++ -*-
/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2017, JSK Lab
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the JSK Lab nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
/*
 * color_histogram_classifier.h
 * Author: Yuki Furuta <furushchev@jsk.imi.i.u-tokyo.ac.jp>
 */

#ifndef JSK_PCL_ROS_COLOR_HISTOGRAM_CLASSIFIER_H__
#define JSK_PCL_ROS_COLOR_HISTOGRAM_CLASSIFIER_H__

#include <dynamic_reconfigure/server.h>
#include <jsk_topic_tools/diagnostic_nodelet.h>
#include <jsk_recognition_msgs/ClusterPointIndices.h>
#include <jsk_recognition_msgs/ColorHistogram.h>
#include <jsk_recognition_msgs/ColorHistogramArray.h>
#include <jsk_recognition_utils/pcl/color_histogram.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/synchronizer.h>
#include <jsk_pcl_ros/ColorHistogramClassifierConfig.h>


namespace jsk_pcl_ros
{
  class ColorHistogramClassifier : public jsk_topic_tools::DiagnosticNodelet
  {
  public:
    typedef ColorHistogramClassifierConfig Config;

    ColorHistogramClassifier() : DiagnosticNodelet("ColorHistogramClassifier"){}
  protected:
    virtual void onInit();
    virtual void configCallback(Config & config, uint32_t level);
    virtual void subscribe();
    virtual void unsubscribe();
    virtual bool loadReference();
    virtual void computeDistance(const std::vector<float>& histogram,
                                 std::vector<double>& distance);
    virtual void feature(const jsk_recognition_msgs::ColorHistogram::ConstPtr& histogram);
    virtual void features(const jsk_recognition_msgs::ColorHistogramArray::ConstPtr& histograms);

    // properties
    boost::mutex mutex_;
    boost::shared_ptr<dynamic_reconfigure::Server<Config> > srv_;
    ros::Subscriber sub_hist_, sub_hists_;
    ros::Publisher pub_class_;

    // parameters
    int queue_size_;
    int bin_size_;
    double detection_threshold_;
    jsk_recognition_utils::ComparePolicy compare_policy_;
    jsk_recognition_msgs::ColorHistogram reference_histogram_;

    std::string classifier_name_;
    std::vector<std::string> label_names_;
    std::vector<std::vector<float> > reference_histograms_;
  };
}

#endif // JSK_PCL_ROS_COLOR_HISTOGRAM_CLASSIFIER_H__
