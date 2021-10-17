// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/canonical_errors.h"
#include <iostream>
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "mediapipe/framework/formats/location_data.pb.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8088
#define MAXLINE 1024
int sockfd;
struct sockaddr_in     servaddr;

constexpr char kLandmarksTag[] = "LANDMARKS";
constexpr char kNormLandmarksTag[] = "NORM_LANDMARKS"; // MAD note @to-fix: streaming NORM_LANDMARKS, but they're labeled LANDMARKS
constexpr char kNormRectTag[] = "NORM_RECT";
constexpr char kDetectionsTag[] = "DETECTIONS";

void setup_udp(){
  // int sockfd;
  char buffer[MAXLINE];
  // char *hello = "Hello from client";
  // struct sockaddr_in     servaddr;

  // Creating socket file descriptor
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  // initial testing for connection
  // while(true){
  //   sendto(sockfd, (const char *)hello, strlen(hello),
  //       0, (const struct sockaddr *) &servaddr,
  //           sizeof(servaddr));
  //   printf("Hello message sent.\n");
  // }
  // close(sockfd);
}

namespace mediapipe {

// A Calculator that simply passes its input Packets and header through,
// unchanged.  The inputs may be specified by tag or index.  The outputs
// must match the inputs exactly.  Any number of input side packets may
// also be specified.  If output side packets are specified, they must
// match the input side packets exactly and the Calculator passes its
// input side packets through, unchanged.  Otherwise, the input side
// packets will be ignored (allowing PassThroughCalculator to be used to
// test internal behavior).  Any options may be specified and will be
// ignored.
class MyPassThroughCalculator : public CalculatorBase {
 public:
  static absl::Status GetContract(CalculatorContract* cc) {
    if (!cc->Inputs().TagMap()->SameAs(*cc->Outputs().TagMap())) {
      return absl::InvalidArgumentError(
          "Input and output streams to MyPassThroughCalculator must use "
          "matching tags and indexes.");
    }
    for (CollectionItemId id = cc->Inputs().BeginId();
         id < cc->Inputs().EndId(); ++id) {
      cc->Inputs().Get(id).SetAny();
      cc->Outputs().Get(id).SetSameAs(&cc->Inputs().Get(id));
    }
    for (CollectionItemId id = cc->InputSidePackets().BeginId();
         id < cc->InputSidePackets().EndId(); ++id) {
      cc->InputSidePackets().Get(id).SetAny();
    }
    if (cc->OutputSidePackets().NumEntries() != 0) {
      if (!cc->InputSidePackets().TagMap()->SameAs(
              *cc->OutputSidePackets().TagMap())) {
        return absl::InvalidArgumentError(
            "Input and output side packets to MyPassThroughCalculator must use "
            "matching tags and indexes.");
      }
      for (CollectionItemId id = cc->InputSidePackets().BeginId();
           id < cc->InputSidePackets().EndId(); ++id) {
        cc->OutputSidePackets().Get(id).SetSameAs(
            &cc->InputSidePackets().Get(id));
      }
    }
    return absl::OkStatus();
  }

  absl::Status Open(CalculatorContext* cc) final {
    for (CollectionItemId id = cc->Inputs().BeginId();
         id < cc->Inputs().EndId(); ++id) {
      if (!cc->Inputs().Get(id).Header().IsEmpty()) {
        cc->Outputs().Get(id).SetHeader(cc->Inputs().Get(id).Header());
      }
    }
    if (cc->OutputSidePackets().NumEntries() != 0) {
      for (CollectionItemId id = cc->InputSidePackets().BeginId();
           id < cc->InputSidePackets().EndId(); ++id) {
        cc->OutputSidePackets().Get(id).Set(cc->InputSidePackets().Get(id));
      }
    }
    cc->SetOffset(TimestampDiff(0));

    setup_udp();

    return absl::OkStatus();
  }

  absl::Status Process(CalculatorContext* cc) final {
    cc->GetCounter("PassThrough")->Increment();
    if (cc->Inputs().NumEntries() == 0) {
      return tool::StatusStop();
    }
    for (CollectionItemId id = cc->Inputs().BeginId();
         id < cc->Inputs().EndId(); ++id) {
      if (!cc->Inputs().Get(id).IsEmpty()) {



        /*-------------------------------------------------------------------*/
        /*------------ EDITS to original pass_through_calculator ------------*/
        /*-------------------------------------------------------------------*/

        if (cc->Inputs().Get(id).Name() == "sub_multi_face_landmarks"){
        // the type is a NormalizedLandmarkList, but you need the kLandmarksTag
        // in order for it not to crash for some reason ...
        //const NormalizedLandmarkList& landmarks = cc->Inputs().Tag(kLandmarksTag).Get<NormalizedLandmarkList>();
        const auto& landmarks_lists = cc->Inputs().Tag(kLandmarksTag).Get<std::vector<NormalizedLandmarkList>>();
        const NormalizedLandmarkList& landmarks = landmarks_lists.front();
        //std::cout << landmarks.landmark_size() << std::endl;
        //VLOG(3) << landmarks.landmark_size() ;
        
        std::string messege;
        for (int i = 0; i < landmarks.landmark_size(); ++i) {
            const NormalizedLandmark& landmark = landmarks.landmark(i);
            //VLOG(3) << "Landmark " << i <<":\n" << landmark.DebugString() << '\n';
            //const auto landmark_debug = landmark.DebugString();
            
            //if (i == 0) std::cout << "Landmark " << i <<":\n" << landmark.DebugString() << '\n';
            // std::cout << landmark.x() << std::endl;
//https://raw.githubusercontent.com/tensorflow/tfjs-models/master/facemesh/mesh_map.jpg
if (i == 105 || i == 125 || i == 1 || i == 0) {
            messege.append("x");
            messege.append(std::to_string(landmark.x()));
            messege.append("y");
            messege.append(std::to_string(landmark.y()));
            messege.append("z");
            messege.append(std::to_string(landmark.z()));
            messege.append(";");
}
        }
         
        //std::cout << messege << std::endl;
        //std::cout << messege.c_str() << std::endl;
         sendto(sockfd, messege.c_str(), messege.length(),
             0, (const struct sockaddr *) &servaddr,
                 sizeof(servaddr));
       }
        

        
                

      /*-------------------------------------------------------------------*/


        VLOG(3) << "Passing " << cc->Inputs().Get(id).Name() << " to "
                << cc->Outputs().Get(id).Name() << " at "
                << cc->InputTimestamp().DebugString();
        cc->Outputs().Get(id).AddPacket(cc->Inputs().Get(id).Value());
      }
    }
    return absl::OkStatus();
  }
};
REGISTER_CALCULATOR(MyPassThroughCalculator);

}  // namespace mediapipe
