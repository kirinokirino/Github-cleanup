import cv2
import mediapipe as mp 
import time

capture = cv2.VideoCapture(0)


config_text = """
# MediaPipe graph that performs face mesh with TensorFlow Lite on GPU.

# Input image. (GpuBuffer)
input_stream: "input_video"

# Collection of detected/processed faces, each represented as a list of
# landmarks. (std::vector<NormalizedLandmarkList>)
output_stream: "multi_face_landmarks"

# Throttles the images flowing downstream for flow control. It passes through
# the very first incoming image unaltered, and waits for downstream nodes
# (calculators and subgraphs) in the graph to finish their tasks before it
# passes through another image. All images that come in while waiting are
# dropped, limiting the number of in-flight images in most part of the graph to
# 1. This prevents the downstream nodes from queuing up incoming images and data
# excessively, which leads to increased latency and memory usage, unwanted in
# real-time mobile applications. It also eliminates unnecessarily computation,
# e.g., the output produced by a node may get dropped downstream if the
# subsequent nodes are still busy processing previous inputs.
node {
  calculator: "FlowLimiterCalculator"
  input_stream: "input_video"
  input_stream: "FINISHED:multi_face_landmarks"
  input_stream_info: {
    tag_index: "FINISHED"
    back_edge: true
  }
  output_stream: "throttled_input_video"
}

# Defines side packets for further use in the graph.
node {
  calculator: "ConstantSidePacketCalculator"
  output_side_packet: "PACKET:num_faces"
  node_options: {
    [type.googleapis.com/mediapipe.ConstantSidePacketCalculatorOptions]: {
      packet { int_value: 1 }
    }
  }
}

# Subgraph that detects faces and corresponding landmarks.
node {
  calculator: "FaceLandmarkFrontCpu"
  input_stream: "IMAGE:throttled_input_video"
  input_side_packet: "NUM_FACES:num_faces"
  output_stream: "LANDMARKS:multi_face_landmarks"
  output_stream: "ROIS_FROM_LANDMARKS:face_rects_from_landmarks"
  output_stream: "DETECTIONS:face_detections"
  output_stream: "ROIS_FROM_DETECTIONS:face_rects_from_detections"
}

"""
graph = mp.CalculatorGraph(graph_config=config_text)
landmarks = []
graph.observe_output_stream(
    'multi_face_landmarks',
    lambda stream_name, packet:
        landmarks.append(mp.packet_getter.get_proto_list(packet)))

rects = []
graph.observe_output_stream(
    'face_rects_from_landmarks',
    lambda stream_name, packet:
        rects.append(mp.packet_getter.get_proto_list(packet)))


previous_time = 0
current_time = 0
contours = None

counter = 1
while counter > 0:
    counter = counter - 1
    graph.start_run()
    success, image = capture.read()
    image.flags.writeable = False
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    image_rgb.flags.writeable = False

    graph.add_packet_to_input_stream(
        'input_video',
        mp.packet_creator.create_image_frame(image_format=mp.ImageFormat.SRGB,
                                            data=image_rgb).at(1))

    #face = results.multi_face_landmarks
    #if face:
    #    mp_draw.draw_landmarks(image, face[0], mp_face_mesh.FACEMESH_CONTOURS, draw_spec, draw_spec)
    #    contours = mp_face_mesh.FACEMESH_CONTOURS

    current_time = time.time()
    fps = 1/(current_time-previous_time)
    previous_time = current_time

    print(fps)

    cv2.imshow("Image", image)
    cv2.waitKey(1)

    graph.close()

if len(landmarks[0]) == 1:
    print(rects[0][0])
    for idx, landmark in enumerate(landmarks[0][0].landmark):
        pass#print(idx, landmark)
